#include "Logic.h"
#include "LCD.h" 
#include "states.h"
#include "MyKeypad.h" 
#include "RGBLed.h"
#include <Arduino.h>
#include "RFID.h"
#include "Buzzer.h"

#define ARRAY_SIZE 4

byte alarmCount = 0; 
char key;
byte inputIndex = 0;
byte failedAttempts = 0;
char inputPassword[] = "****";
char correctPassword[] = "1234";


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
  if(varTargetValue > 1) changeState(INPUT_PMV_HIGH);
  else {
    if(varTargetValue < -1) changeState(INPUT_PMV_LOW);
  }
}
void onAlarm(){
  if(alarmCount == 3) changeState(INPUT_WRONG);
  else {
    soundAlarm();     
    startRGBAlarm();  
    alarmCount++;
  }
}

void onPMVHigh(){
  startTime();
  if(stateTime >= 7000) changeState(INPUT_CORRECT);
  else ShowGreen();
}
void onPMVLow(){
  startTime();
  if(stateTime >= 4000) changeState(INPUT_CORRECT);
  else ShowBlue();  
}

void changeState(Input newInput){
  currentInput = newInput;
  ResetAll();
}
void ResetPassword(){
  for (byte idx = 0; idx < ARRAY_SIZE; idx++) inputPassword[idx] = '*';   
}
void ResetVars(){
    inputIndex = key = 0;
}
void ResetAll(){
  failedAttempts = 0;
  restartTimes();
  ResetPassword(); 
  ResetVars();
}