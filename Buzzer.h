#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>
#include <AsyncTaskLib.h>

#define buzzerPin 13

void setupBuzzer();
void updateBuzzer();
void startBuzzer();
void resetBuzzer();
void stopBuzzer();
void OnBuzzer();
void OffBuzzer();

#endif
