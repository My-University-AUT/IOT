// #include <Arduino.h>
#include "HX711.h"
#include <Wire.h>
#include <Servo.h>
#include <TimeLib.h>

const int BUTTON_PIN = 26;
const int BUZZER_PIN = 22;
const int VIBRATION_SENSOR_PIN = 25;
const int GREEN_LED_PIN = 24;
const int RED_LED_PIN = 23;

bool is_alerting = false;
bool is_on = true;
unsigned long last_debounce_time = 0;

void set_leds(bool is_sec_system_active);
void send_sms();

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(VIBRATION_SENSOR_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  delay(100);
  set_leds(is_on);
}

void loop()
{
  int button_state = digitalRead(BUTTON_PIN);
  unsigned long current_time = millis();

  if (button_state == LOW && current_time - last_debounce_time > 200) {
    last_debounce_time = current_time;
    is_on = !is_on;
    set_leds(is_on);
  }

  if (is_on && !is_alerting && digitalRead(VIBRATION_SENSOR_PIN) == HIGH) {
    is_alerting = true;
    digitalWrite(BUZZER_PIN, HIGH);
    send_sms();
  }
  else if (!is_on && is_alerting) {
    is_alerting = false;
    digitalWrite(BUZZER_PIN, LOW);
  }

  if (Serial3.available() > 0) {
    Serial.write(Serial3.read());
  }
}

void set_leds(bool is_sec_system_active)
{
  digitalWrite(GREEN_LED_PIN, is_sec_system_active ? HIGH : LOW);
  digitalWrite(RED_LED_PIN, is_sec_system_active ? LOW : HIGH);
}

void send_sms()
{
  Serial3.print("AT+CMGS=\"09092301202\"\r");
  delay(100);
  Serial3.print("Zangole\r");
  delay(100);
  Serial3.write(0x1A);
  delay(100);
  Serial3.print("\r");
}
