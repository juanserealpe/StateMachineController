LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setupLCD() {
  lcd.begin(16, 2);
}

void showWelcomeMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ingresa clave:");
}

void showAccessGranted() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acceso concedido");
}

void showAccessDenied() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clave incorrecta");
  delay(1500);
}

void printAsterisk(int pos) {
  lcd.setCursor(pos, 1);
  lcd.print("*");
}
