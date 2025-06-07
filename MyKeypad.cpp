#include "MyKeypad.h"

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[KEYPAD_ROWS] = {28, 30, 33, 34};
byte colPins[KEYPAD_COLS] = {36, 38, 40, 42};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

void setupKeypad(){

}