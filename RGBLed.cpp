#include "RGBLed.h"
#include <Arduino.h>

// Variables para el parpadeo durante la alarma
bool ledAlarmActive = false;
bool ledState = false;
unsigned long ledAlarmStartTime = 0;
unsigned long lastLedToggleTime = 0;

const short LED_ALARM_DURATION = 5000;
const short LED_ON_TIME = 200;
const short LED_OFF_TIME = 100;

void StartRGB() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}
void OffRGB() {
  ShowRGB(0,0,0);
}
void ShowRGB(unsigned char red, unsigned char green, unsigned char blue) {
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}
void ShowRed(){
  ShowRGB(255,0,0);
}
void ShowGreen(){
  ShowRGB(0,255,0);
}
void ShowBlue(){
  ShowRGB(0,0,255);
}

void startRGBAlarm() {
  ledAlarmActive = true;
  ledAlarmStartTime = millis();
  lastLedToggleTime = millis();
  ledState = true;
  ShowRed(); // Empieza encendido
}

void updateRGBAlarm() {
  if (!ledAlarmActive) return;

  unsigned long currentTime = millis();

  if (currentTime - ledAlarmStartTime >= LED_ALARM_DURATION) {
    OffRGB();
    ledAlarmActive = false;
    return;
  }

  if (ledState && (currentTime - lastLedToggleTime >= LED_ON_TIME)) {
    OffRGB();
    ledState = false;
    lastLedToggleTime = currentTime;
  }
  else if (!ledState && (currentTime - lastLedToggleTime >= LED_OFF_TIME)) {
    ShowRed();
    ledState = true;
    lastLedToggleTime = currentTime;
  }
}