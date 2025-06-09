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
void StartRGB();
void OffRGB();
void setupRGB();
void updateRGB();
void startAlarmLed();
void resetRGB();
void EndBlink();
void OnRed();

#endif