#include "States.h"
#include "Logic.h"
#include "LCD.h"  
#include "Buzzer.h"
#include "MyKeypad.h"
#include "TemperatureSensor.h"
#include "RGBLed.h"
#include "RFID.h"
#include <SPI.h>
#include <MFRC522.h>

void setup() {
  Serial.begin(9600);
  StartRGB();
  setupStateMachine();
  setupLCD();       
  setupRFID();   
  setupBuzzer();     
  setupTemperature(); 
  //setupLCD();
}

void loop() {
  stateMachine.Update();
}
