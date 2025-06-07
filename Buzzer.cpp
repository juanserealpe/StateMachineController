#include "Buzzer.h"
#include <Arduino.h>

// Variables para el buzzer básico
unsigned long buzzerStartTime = 0;
bool buzzerActive = false;
short buzzerDuration = 0;

// Variables para la alarma
unsigned long alarmStartTime = 0;
unsigned long lastBeepChangeTime = 0;
bool alarmActive = false;
bool beepState = false;
const short ALARM_DURATION = 5000; // 5 segundos total
const short BEEP_DURATION = 200;   // 200ms encendido
const short PAUSE_DURATION = 100;  // 100ms apagado

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void startBuzzer(short duration) {
  digitalWrite(buzzerPin, HIGH);
  buzzerStartTime = millis();
  buzzerDuration = duration;
  buzzerActive = true;
  alarmActive = false;
}

void updateBuzzer() {
  if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
    digitalWrite(buzzerPin, LOW);
    buzzerActive = false;
  }
}

void soundBuzzer() {
  startBuzzer(1000); 
} 

void soundAlarm() {
  alarmStartTime = millis();
  lastBeepChangeTime = millis();
  alarmActive = true;
  beepState = true;
  digitalWrite(buzzerPin, HIGH);
}

void updateAlarm() {
  if (!alarmActive) return;
  
  unsigned long currentTime = millis();
  
  if (currentTime - alarmStartTime >= ALARM_DURATION) {
    digitalWrite(buzzerPin, LOW);
    alarmActive = false;
    return;
  }
  
  if (beepState && (currentTime - lastBeepChangeTime >= BEEP_DURATION)) {
    digitalWrite(buzzerPin, LOW);
    beepState = false;
    lastBeepChangeTime = currentTime;
  }
  else if (!beepState && (currentTime - lastBeepChangeTime >= PAUSE_DURATION)) {
    digitalWrite(buzzerPin, HIGH);
    beepState = true;
    lastBeepChangeTime = currentTime;
  }
}