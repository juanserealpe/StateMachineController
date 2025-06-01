String inputPassword = "";
const String correctPassword = "1234";

void readKeypad() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    handleKey(key);
  }
}

void handleKey(char key) {
  inputPassword += key;
  printAsterisk(inputPassword.length() - 1);

  if (inputPassword.length() == 4) {
    delay(500);
    checkPassword();
  }
}

void checkPassword() {
  if (inputPassword == correctPassword) {
    showAccessGranted();
    soundBuzzer();
  } else {
    showAccessDenied();
  }
  resetInput();
}

void resetInput() {
  inputPassword = "";
  showWelcomeMessage();
}
