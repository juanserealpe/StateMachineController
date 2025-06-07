#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#define buzzerPin 13

void setupBuzzer();
void startBuzzer(short duration);
void updateBuzzer();
void soundBuzzer();

#endif
