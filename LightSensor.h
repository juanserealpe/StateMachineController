#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

#define PIN_LIGHTSENSOR A0

extern int LightValue;  // <- IMPORTANTE: esta línea exporta la variable

void setupLightSensor();
int readLightSensor();
#endif
