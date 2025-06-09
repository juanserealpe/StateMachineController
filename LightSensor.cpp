#include "LightSensor.h"

int LightValue = 0;

void setupLightSensor() {
  pinMode(PIN_LIGHTSENSOR, INPUT);
}

int readLightSensor() {
  LightValue = analogRead(PIN_LIGHTSENSOR); 
  return LightValue;
}

