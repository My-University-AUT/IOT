// // #include <Arduino.h>
// #include "HX711.h"
// #include <Wire.h>
// #include <Servo.h>
// #include <TimeLib.h>

// #define TIME_MSG_LEN 11 // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
// #define TIME_HEADER 'T' // Header tag for serial time sync message
// #define TIME_REQUEST 7  // ASCII bell character requests a time sync message

// Servo servo;
// const int servoPin = 11;

// const int buzzerPin = 15;
// const int rainingPin = 27;
// const int soilMoisturePin = A0;

// const int LDRPin = A1; // Initialize PIN A0 LDR PIN

// // HX711 circuit wiring
// const int LOADCELL_SCK_PIN = 2;
// const int LOADCELL_DOUT_PIN = 3;

// HX711 scale;

// void waterTheLand();
// void printDigits(int digits);
// void processSyncMessage();
// void digitalClockDisplay();
// bool checkItIsRaining();
// bool isTheSunLightTooMuch();
// bool checkSoilMoistureIsEnough();

// // T1262347200 --> timestamp // Jan 1 2010
// // T1682206406 --> timestamp // Apr 4 2023

// // 8:00, 12:00 and 16:00
// void setup()
// {
//     Serial1.begin(9600);

//     scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
//     scale.set_scale(36.059);

//     servo.attach(servoPin);
//     pinMode(rainingPin, INPUT);
// }

// void loop()
// {

//     // while(timeStatus() == timeNotSet) {
//     //     Serial1.println("waiting for sync message");
//     //     if (Serial1.available())
//     //     {
//     //         processSyncMessage();
//     //     }
//     //     delay(1000);
//     // }
//     // digitalClockDisplay();


//     const int lightIsTooHigh = isTheSunLightTooMuch();
//     const int itIsRaining = checkItIsRaining();
//     const int soilMoistureIsEnough = checkSoilMoistureIsEnough();
//     if(!lightIsTooHigh && !itIsRaining && !soilMoistureIsEnough) {
//         waterTheLand();
//     }
//     delay(1000);
// }

// void waterTheLand()
// {
//     for (int pos = 0; pos <= 180; pos += 1)
//     {
//         servo.write(pos);
//         delay(15);
//     }
// }

// // syncing board clock: https://playground.arduino.cc/Code/Time/

// void digitalClockDisplay()
// {
//     // digital clock display of the time
//     Serial1.print(hour());
//     printDigits(minute());
//     printDigits(second());
//     Serial1.print(" ");
//     Serial1.print(day());
//     Serial1.print(" ");
//     Serial1.print(month());
//     Serial1.print(" ");
//     Serial1.print(year());
//     Serial1.println();
// }

// void printDigits(int digits)
// {
//     // utility function for digital clock display: prints preceding colon and leading 0
//     Serial1.print(":");
//     if (digits < 10)
//         Serial1.print('0');
//     Serial1.print(digits);
// }

// void processSyncMessage()
// {
//     // if time sync available from serial port, update time and return true
//     while (Serial1.available() >= TIME_MSG_LEN)
//     { // time message consists of header & 10 ASCII digits
//         char c = Serial1.read();
//         Serial1.print(c);
//         if (c == TIME_HEADER)
//         {
//             time_t pctime = 0;
//             for (int i = 0; i < TIME_MSG_LEN - 1; i++)
//             {
//                 c = Serial1.read();
//                 if (c >= '0' && c <= '9')
//                 {
//                     pctime = (10 * pctime) + (c - '0'); // convert digits to a number
//                 }
//             }
//             setTime(pctime); // Sync Arduino clock to the time received on the serial port
//         }
//     }
// }

// bool checkItIsRaining()
// {
//     int itIsRaining = digitalRead(27);

//     if (itIsRaining == 1)
//     {
//         Serial1.println("Its Raining");
//         return true;
//     }
//     else if (itIsRaining == 0)
//     {
//         Serial1.println("No Rain");
//         return false;
//     }
// }

// bool checkSoilMoistureIsEnough()
// {
//     const int value = analogRead(soilMoisturePin);
//     const int s = map(value, 0, 1023, 0, 255);
//     if (s > 200)
//     {
//         Serial1.println("moisture is high " + String(s));
//         return true;
//     }
//     else
//     {
//         Serial1.println("moisture is low " + String(s));
//         return false;
//     }
// }

// bool isTheSunLightTooMuch()
// {
//     int ldrStatus = analogRead(LDRPin);
//     if (ldrStatus > 500)
//     {
//         Serial1.println("light is enough");
//         return true;
//     }
//     else
//     {
//         Serial1.println("light is not enough");
//         return false;
//     }
// }