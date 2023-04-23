// #include <Arduino.h>
#include "HX711.h"
#include <Wire.h>
#include <Servo.h>
#include <TimeLib.h>

#define TIME_MSG_LEN 11 // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER 'T' // Header tag for serial time sync message
#define TIME_REQUEST 7 // ASCII bell character requests a time sync message


Servo servo;
const int servoPin = 11;

const int buzzerPin = 15;

// HX711 circuit wiring
const int LOADCELL_SCK_PIN = 2;
const int LOADCELL_DOUT_PIN = 3;

HX711 scale;

void fillThePlate();
void printDigits(int digits);
void processSyncMessage();
void digitalClockDisplay();
bool checkTimeToFillPlate();
void turnOffBuzzer();
void turnOnBuzzer();

// T1262347200 --> timestamp // Jan 1 2010
// T1682206406 --> timestamp // Apr 4 2023

// 8:00, 12:00 and 16:00
int timeToFillThePlate[3][2] = {{8,0}, {12,0}, {16, 0}};

void setup()
{
    Serial1.begin(9600);

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(36.059);

    servo.attach(servoPin);
}

void loop()
{

    // while(timeStatus() == timeNotSet) {
    //     Serial1.println("waiting for sync message");
    //     if (Serial1.available())
    //     {
    //         processSyncMessage();
    //     }
    //     delay(1000);
    // }
    // digitalClockDisplay();

    const int value = analogRead(A0);
    const int s = map(value, 0, 1023, 0, 255);
    if(s > 200) {
        Serial1.println("moisture is high "+ String(s));
    } else {
        Serial1.println("moisture is low "+ String(s));
    }
    delay(1000);
}

void fillThePlate()
{
    for (int pos = 0; pos <= 180; pos += 1)
    {
        servo.write(pos);
        delay(15);
    }
}

// syncing board clock: https://playground.arduino.cc/Code/Time/

void digitalClockDisplay()
{
    // digital clock display of the time
    Serial1.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial1.print(" ");
    Serial1.print(day());
    Serial1.print(" ");
    Serial1.print(month());
    Serial1.print(" ");
    Serial1.print(year());
    Serial1.println();
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial1.print(":");
    if (digits < 10)
        Serial1.print('0');
    Serial1.print(digits);
}

void processSyncMessage()
{
    // if time sync available from serial port, update time and return true
    while (Serial1.available() >= TIME_MSG_LEN)
    { // time message consists of header & 10 ASCII digits
        char c = Serial1.read();
        Serial1.print(c);
        if (c == TIME_HEADER)
        {
            time_t pctime = 0;
            for (int i = 0; i < TIME_MSG_LEN - 1; i++)
            {
                c = Serial1.read();
                if (c >= '0' && c <= '9')
                {
                    pctime = (10 * pctime) + (c - '0'); // convert digits to a number
                }
            }
            setTime(pctime); // Sync Arduino clock to the time received on the serial port
        }
    }
}

bool checkTimeToFillPlate() {
    const int nowHour = hour();
    const int nowMinute = minute();
    for(int i=0; i< 3; i++) {
        const int hour = timeToFillThePlate[i][0];
        const int min = timeToFillThePlate[i][1];
        if( nowHour == hour && nowMinute == min) {
            return true;
        }
    }
    return false;
}

void turnOnBuzzer() {
    const int freq = 1000;
    tone(buzzerPin, freq, 10000);
}

void turnOffBuzzer() {
    noTone(buzzerPin);
}