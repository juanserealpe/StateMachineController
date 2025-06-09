#include "HardwareSerial.h"
#include "Logic.h"
#include "LCD.h" 
#include "MyKeypad.h" 
#include "RGBLed.h"
#include "RFID.h"
#include "Buzzer.h"
#include "states.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"

#define ARRAY_SIZE 4

void TimeOut();

unsigned long currentTimeOut = 0;
int alarmCount = 0; 
char key;
bool fromAlarm = false;
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
  resetRGB();
  OffRGB();
  showMonitoringSystem();
  updateTemperature();
  short varTargetValue = readTarget();
  readLightSensor();
  //Serial.println(currentTemperature);
  if(LightValue < 10 || currentTemperature > 40.0){
    changeState(INPUT_ALARM);
  }
  if(varTargetValue > 1) {
    //changeState(INPUT_PMV_HIGH);
    changeState(INPUT_ALARM);
    }
  else {
    if(varTargetValue < -1) {changeState(INPUT_PMV_LOW);}
  }
}

void onAlarm(){ 
  fromAlarm = true;
  startAlarmLed(); 
  if(!TaskTimeOut.IsActive()){ 
    TaskTimeOut.SetIntervalMillis(5000); 
    TaskTimeOut.Start(); 
    stopBuzzer(); 
  } 
  if(!buzzerActive) startBuzzer(); 
  updateBuzzer(); 
  ShowMessage1("En alarma");
} 

void onPMVHigh(){

  resetRGB();
  OffRGB();

  Serial.println("Entrando en HIGH...");
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(7000);
    TaskTimeOut.Start();
    RestartAllLCD();
  } 
  ShowMessage1("En PmVHigh");
}
void onPMVLow(){
  Serial.println("Entrando en LOW...");
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(4000);
    TaskTimeOut.Start();
    RestartAllLCD();
  } 
    ShowMessage1("En PmVLow");
    
    resetRGB();   // Siempre antes
    ShowRed();    // Encender manualmente
}

void changeState(Input newInput){
  currentInput = newInput;
  ResetAll();
}
void TimeOut(){
  if(fromAlarm) alarmCount++;
  else alarmCount = 0;
  fromAlarm = false;
  Serial.print(alarmCount);    
  if(alarmCount >= 3) { 
    alarmCount = 0; 
    resetBuzzer(); 
    changeState(INPUT_WRONG); 
    return;
  } 
    changeState(INPUT_CORRECT);
}
void ResetPassword(){
  for (byte idx = 0; idx < ARRAY_SIZE; idx++) inputPassword[idx] = '*';   
}
void ResetVars(){
    inputIndex = key = 0;
    fromAlarm = false;
}
void ResetAll(){
  failedAttempts = 0;
  resetBuzzer(); 
  TaskTimeOut.Reset();
  RestartAllLCD();
  ResetPassword(); 
  ResetVars();
}