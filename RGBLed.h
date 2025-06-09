#ifndef RGBLed_H
#define RGBLed_H
#include <Arduino.h>
#include "AsyncTaskLib.h"
#define PIN_RED 8
#define PIN_GREEN 9
#define PIN_BLUE 10

void ShowRGB(unsigned char red, unsigned char green, unsigned char blue);
void ShowRed();
void ShowGreen();
void ShowBlue();
void startBucleLed(int prmNum);
void StartRGB();
void OffRGB();
void setupRGB();
void updateRGB();
void stopAlarmLed();
void startAlarmLed(unsigned int onTime = 200, unsigned int offTime = 100, unsigned int totalTime = 5000);
void resetRGB();
void EndBlink();
void OnRed();

#endif