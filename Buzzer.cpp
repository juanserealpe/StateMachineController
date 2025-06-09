#include "Buzzer.h"
#define TimeOnAlarm 200
#define TimeOffAlarm 100

AsyncTask TaskBuzzerONAlarm(TimeOnAlarm, false, OnBuzzer);
AsyncTask TaskBuzzerOFFAlarm(TimeOffAlarm, false, OffBuzzer);
bool buzzerActive = false;

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void updateBuzzer(){
  TaskBuzzerONAlarm.Update();
  TaskBuzzerOFFAlarm.Update();
}

void startBuzzer(){
  if(buzzerActive) return;  // Ya está activo
  
  buzzerActive = true;
  digitalWrite(buzzerPin, HIGH);  // Comienza encendido
  TaskBuzzerONAlarm.SetIntervalMillis(TimeOnAlarm);
  TaskBuzzerOFFAlarm.SetIntervalMillis(TimeOffAlarm);
  TaskBuzzerONAlarm.Start();
  TaskBuzzerOFFAlarm.Start();
}

void resetBuzzer(){
  TaskBuzzerONAlarm.Stop();
  TaskBuzzerOFFAlarm.Stop();
  digitalWrite(buzzerPin, LOW);
  buzzerActive = false;
}

void stopBuzzer(){
  resetBuzzer();  // Reutiliza la misma lógica
}

void OnBuzzer(){
  digitalWrite(buzzerPin, HIGH);
  TaskBuzzerOFFAlarm.Start();  // Programar el apagado
}

void OffBuzzer(){
  digitalWrite(buzzerPin, LOW);
  TaskBuzzerONAlarm.Start();  // Programar el encendido
}