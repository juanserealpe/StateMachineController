#include "RGBLed.h"
#include <Arduino.h>

void StartRGB() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}
void OffRGB() {
  ShowRGB(0,0,0);
}
void ShowRGB(unsigned char red, unsigned char green, unsigned char blue) {
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}
void ShowRed(){
  ShowRGB(255,0,0);
}
void ShowGreen(){
  ShowRGB(0,255,0);
}
void ShowBlue(){
  ShowRGB(0,0,255);
}
