#include <LiquidCrystal.h>
#include <Keypad.h>

void setup() {
  setupLCD();
  setupBuzzer();
  showWelcomeMessage();
}

void loop() {
  readKeypad();
  updateBuzzer();
}
