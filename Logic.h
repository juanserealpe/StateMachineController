#ifndef LOGIC_H
#define LOGIC_H

#include <Arduino.h>
#include <Keypad.h>
#include "states.h"
//Externse
extern byte indx;
extern char key;
extern byte inputIndex;
extern byte failedAttempts;
extern char inputPassword[];
extern char correctPassword[];
//Time
extern unsigned long StartTimePmvHigh;
extern unsigned long StartTimePmvLow;
extern unsigned long StartTImeAlarm;

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
