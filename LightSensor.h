#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#define PIN_LIGHTSENSOR 4
#include <Arduino.h>

extern int LightValue;

void setupLightSensor();
void ReadLightSensor();

#endif