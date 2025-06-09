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
  resetBuzzer();
  TaskBuzzerONAlarm.Start();
  TaskBuzzerOFFAlarm.Start();
}
void resetBuzzer(){
  TaskBuzzerONAlarm.Reset();
  TaskBuzzerOFFAlarm.Reset();
  buzzerActive = false;
}
void stopBuzzer(){
  TaskBuzzerONAlarm.Stop();
  TaskBuzzerOFFAlarm.Stop(); 
  buzzerActive = false; 
}
void OnBuzzer(){
  if(buzzerActive) return;
  digitalWrite(buzzerPin, HIGH);
  buzzerActive = true;
}
void OffBuzzer(){
  if(!buzzerActive) return;
  digitalWrite(buzzerPin, LOW);
  buzzerActive = false;
}