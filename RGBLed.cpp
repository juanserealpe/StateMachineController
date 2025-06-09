#include "RGBLed.h"

unsigned long LED_ON_TIME;
unsigned long LED_OFF_TIME;
bool LedOn = false;

void StartRGB() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}
void OffRGB() {
  if(!LedOn) return;
  ShowRGB(0,0,0);
  LedOn = false;
}
void ShowRGB(unsigned char red, unsigned char green, unsigned char blue) {
  if(LedOn) return;
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
  LedOn = true;
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
