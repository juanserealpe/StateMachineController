#include "LCD.h"
#include <Arduino.h>
#define MessageDuration 500

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned long TimeStart = 0;
unsigned long TimeMessage = 0;
bool ShowingMessage = false;

void setupLCD() {
  lcd.begin(16, 2);
}

void showWelcomeMessage() {
  ShowMessage("Ingresa clave: ");
}

void showAccessGranted() {
  ShowMessage("Acceso OK", MessageDuration);
}


void showAccessDenied() {
  ShowMessage("Clave incorrecta");
}

void showBlockSystem() {
  ShowMessage("Bloqueado");
}

void printAsterisk(byte pos) {
  lcd.setCursor(pos, 1);
  lcd.print("*");
}
void ShowMessage(const char* pMessage, unsigned long pTime){
  RestartOutput();
  TimeMessage = pTime;
  lcd.print(pMessage);
  TimeStart = millis();
  ShowingMessage = true;
}
void ShowMessage(const char* pMessage){
  if(ShowingMessage) return;
  RestartOutput();
  lcd.print(pMessage);
  ShowingMessage = true;
}

void UpdateLCDMessage(){
  if(!ShowingMessage) return;
  if((millis() - TimeStart) < TimeMessage) return;
  RestartOutput();
}

void RestartOutput(){
  lcd.clear();
  lcd.setCursor(0, 0);
  ShowingMessage = false;
}