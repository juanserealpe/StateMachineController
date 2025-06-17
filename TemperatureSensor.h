#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void setupTemperature();
void updateTemperature();
extern float currentTemperature;

#endif
