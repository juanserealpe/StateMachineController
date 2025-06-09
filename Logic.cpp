#include "HardwareSerial.h"
#include "Logic.h"
#include "LCD.h" 
#include "MyKeypad.h" 
#include "RGBLed.h"
#include "RFID.h"
#include "Buzzer.h"
#include "states.h"

#define ARRAY_SIZE 4

void TimeOut();

unsigned long currentTimeOut = 0;
byte alarmCount = 0; 
char key;
byte inputIndex = 0;
byte failedAttempts = 0;
char inputPassword[] = "****";
char correctPassword[] = "1234";
AsyncTask TaskTimeOut(currentTimeOut, false, TimeOut);

bool readKeypad() {
  key = keypad.getKey();
  return (key != NO_KEY);
}

void handleKey() {
  if(key == '#') checkPassword();
  else {
    printAsterisk(inputIndex);
    if(inputIndex < 4) {
      inputPassword[inputIndex] = key;
      Serial.println(inputPassword[inputIndex]);//
    }
    inputIndex++;
  }
}

bool Equals(char* pChar1, char* pChar2) {
  return (memcmp(pChar1, pChar2,ARRAY_SIZE) == 0);
}

void checkPassword() {
  Serial.println("Checando Password");//Delete
  if(Equals(inputPassword, correctPassword)){
    Serial.println("Contraseña correcta");//Delete
    showAccessGranted();
    changeState(INPUT_CORRECT);
    }
  else incorrectPassword();
}

void incorrectPassword(){
  Serial.println("Contraseña incorrecta");//Delete
  showAccessDenied();
  failedAttempts++;
  Serial.println(failedAttempts);//Delete
  ResetVars();
  ResetPassword();
}
void onInit() {
  showWelcomeMessage();
  if(failedAttempts == 3) changeState(INPUT_WRONG);
  else { if(readKeypad()) handleKey(); }
}

void onBlocked(){
  showBlockSystem();
  if(readKeypad()) { 
    if(key == '#') {
      changeState(INPUT_NULL);  
    }
  }
}
void onMonitoring(){
  showMonitoringSystem();
  short varTargetValue = readTarget();
//
  if(alarmCount == 0 && varTargetValue == 0) changeState(INPUT_ALARM);
  if(varTargetValue > 1) {changeState(INPUT_PMV_HIGH);}
  else {
    if(varTargetValue < -1) {changeState(INPUT_PMV_LOW);}
  }
}
void onAlarm(){
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(5000);
    TaskTimeOut.Start();
    stopBuzzer();
  }
  TaskTimeOut.Update();
  if(alarmCount == 2) {
    alarmCount = 0;
    resetBuzzer();
    changeState(INPUT_WRONG);
  }
  showAccessGranted();
  //Serial.println("En Alarma...");
  if(!buzzerActive) startBuzzer();
  updateBuzzer();
}

void onPMVHigh(){
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(7000);
    TaskTimeOut.Start();
    RestartAllLCD();
  } 
  ShowMessage1("En PmVHigh");
  //Encencer calentador
}
void onPMVLow(){
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(4000);
    TaskTimeOut.Start();
    RestartAllLCD();
  } 
    ShowMessage1("En PmVLow");
  //Hacer lo otro  
}

void changeState(Input newInput){
  currentInput = newInput;
  ResetAll();
}
void TimeOut(){
  Serial.print(alarmCount);
  resetBuzzer();
  if(currentInput == INPUT_ALARM) alarmCount++;
  else {
    changeState(INPUT_CORRECT);
    alarmCount = 0;
  }
  Serial.print(alarmCount);  
}
void ResetPassword(){
  for (byte idx = 0; idx < ARRAY_SIZE; idx++) inputPassword[idx] = '*';   
}
void ResetVars(){
    inputIndex = key = 0;
}
void ResetAll(){
  failedAttempts = 0;
  TaskTimeOut.Reset();
  RestartAllLCD();
  ResetPassword(); 
  ResetVars();
}