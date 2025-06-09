#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>
#include <Arduino.h>
#include <AsyncTaskLib.h>

#define MessageDuration 1000

extern LiquidCrystal lcd;
extern AsyncTask TaskclearLcd;

void setupLCD();
// 
void showWelcomeMessage();
void showAccessGranted();
void showAccessDenied();
void showBlockSystem();
void showMonitoringSystem();
//
void printAsterisk(byte pos);
void ShowMessage(const char* pMessage, unsigned long pTime = 0);
void ShowMessage1(const char* pMessage);
//
void RestartOutputLCD();
void RestartAllLCD();
#endif