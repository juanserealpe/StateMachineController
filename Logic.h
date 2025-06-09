#ifndef LOGIC_H
#define LOGIC_H
#include <DHT.h>

#define DHTPIN 22  
#define DHTTYPE DHT11
#define PIN_FOTORESISTOR A0

#include <Arduino.h>
#include <Keypad.h>
#include <AsyncTaskLib.h>
#include "states.h"
//Externse
extern DHT dht;
extern int alarmCount;
extern byte indx;
extern char key;
extern byte inputIndex;
extern byte failedAttempts;
extern char inputPassword[];
extern char correctPassword[];
extern int CurrentLightValue;
extern float CurrentTemperature;
extern float Currenthumidity;
//Time
extern AsyncTask TaskTimeOut;

//Init
bool readKeypad();
void handleKey();
bool Equals(char* pChar1, char* pChar2);
void checkPassword();
void incorrectPassword();
//States Controllers
void onInit();
void onMonitoring();
void onBlocked();
void onAlarm();
void onPMVHigh();
void onPMVLow();

//Transition
void changeState(Input newInput);

//Cleaners
void ResetPassword();
void ResetVars();
void ResetAll();

#endif
