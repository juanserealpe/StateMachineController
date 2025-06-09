#include "LCD.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool ShowingMessageWithoutTime = false;
bool ShowingMessageWithTime = false;
AsyncTask TaskclearLcd(MessageDuration, false, RestartAllLCD);

void setupLCD() {
  lcd.begin(16, 2);
}

void showWelcomeMessage() {
  ShowMessage1("Ingresa clave: ");
}

void showAccessGranted() {
  ShowMessage("Acceso OK", MessageDuration);
}


void showAccessDenied() {
  ShowMessage("Clave incorrecta", MessageDuration);
}

void showBlockSystem() {
  ShowMessage1("Bloqueado");
}
void showMonitoringSystem() {
  ShowMessage1("Monitoreando");
}

void printAsterisk(byte pos) {
  lcd.setCursor(pos, 1);
  lcd.print("*");
}
void ShowMessage(const char* pMessage, unsigned long pTime){
  if(ShowingMessageWithTime) return;
  TaskclearLcd.Reset();
  TaskclearLcd.Start();
  ShowingMessageWithTime = true;
  ShowingMessageWithoutTime = false;
  ShowMessage1(pMessage);
  return;
} 
void ShowMessage1(const char* pMessage){
  if(ShowingMessageWithoutTime) return;
  RestartOutputLCD();
  lcd.print(pMessage);
  ShowingMessageWithoutTime = true;
}
void RestartOutputLCD(){
  lcd.clear();
  lcd.setCursor(0, 0);
}
void RestartAllLCD(){
  RestartOutputLCD();
  TaskclearLcd.Reset();
  ShowingMessageWithTime = ShowingMessageWithoutTime = false;
}