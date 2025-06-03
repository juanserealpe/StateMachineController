#include <LiquidCrystal.h>
#include <Keypad.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "States.h"

extern SystemState currentState;


void setup() {
  setupLCD();          
  setupBuzzer();     
  setupTemperature();  
  showWelcomeMessage();
}

void loop() {
  readKeypad();
  updateBuzzer();
  updateTemperature(); 
}

