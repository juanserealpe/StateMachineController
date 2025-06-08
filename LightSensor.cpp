#include "LightSensor.h"

int LightValue = 0;

void setupLightSensor() {
  pinMode(PIN_LIGHTSENSOR, INPUT);
}

void ReadLightSensor() {
  LightValue = analogRead(PIN_LIGHTSENSOR);
}