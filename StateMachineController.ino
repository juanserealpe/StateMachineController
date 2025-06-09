#include "States.h"
#include "Logic.h"
#include "LCD.h"  
#include "Buzzer.h"
#include "MyKeypad.h"
#include "TemperatureSensor.h"
#include "RGBLed.h"
#include "RFID.h"

void setup() {
  Serial.begin(9600);
  setupBuzzer();  
  setupStateMachine();
  setupLCD();       
  setupRFID();   
  setupBuzzer(); 
  setupRGB();    
  setupTemperature();
  setupTemperature();
  setupRFID();
}

void loop() {
  stateMachine.Update();
  TaskclearLcd.Update();
  TaskTimeOut.Update();
  updateRGB();
  updateBuzzer();
}