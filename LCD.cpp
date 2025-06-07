#include "LCD.h"
#include <Arduino.h>
#define MessageDuration 1500

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
  ShowMessage("Clave incorrecta", MessageDuration);
}

void showBlockSystem() {
  ShowMessage("Bloqueado");
}
void showMonitoringSystem() {
  ShowMessage("Monitoreando");
}

void printAsterisk(byte pos) {
  lcd.setCursor(pos, 1);
  lcd.print("*");
}
void ShowMessage(const char* pMessage, unsigned long pTime){

  if(TimeStart == 0) ShowingMessage = false;
  ShowMessage(pMessage);
  TimeStart = millis();
  TimeMessage = pTime;
  return;
} 
void ShowMessage(const char* pMessage){
  if(ShowingMessage) return;
  RestartOutput();
  lcd.print(pMessage);
  ShowingMessage = true;
}

void UpdateLCDMessage(){
  if(!ShowingMessage) return;
  if(TimeStart == 0) return;
  if((millis() - TimeStart) < TimeMessage) return;
  RestartAll();
}

void RestartOutput(){
  lcd.clear();
  lcd.setCursor(0, 0);
}
void RestartAll(){
  RestartOutput();
  ShowingMessage = false;
  TimeStart = TimeMessage = 0 ; 
}