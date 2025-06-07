#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void setupLCD();

//ShowMessagePredefined
void showWelcomeMessage();
void showAccessGranted();
void showAccessDenied();
void showBlockSystem();
void showMonitoringSystem();
void printAsterisk(byte pos);
//ShowMessageCustom
void ShowMessage(const char* pMessage, unsigned long pTime);
void ShowMessage(const char* pMessage);
//Updtate & restart.
void updateLCDMessage();
void RestartOutput();
void RestartAll();
#endif
