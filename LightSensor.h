#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

#define PIN_LIGHTSENSOR A0

extern int LightValue;  

void setupLightSensor();
int readLightSensor();
#endif
