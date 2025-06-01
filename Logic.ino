// States's system
enum SystemState {
  STATE_WAITING_INPUT,
  STATE_PROCESSING,
  STATE_ACCESS_GRANTED,
  STATE_ACCESS_DENIED,
  STATE_BLOCKED
};
//Current state:
SystemState currentState = STATE_WAITING_INPUT;

int failedAttempts = 0;
String inputPassword = "";
const String correctPassword = "1234";

void readKeypad() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    handleKey(key);
  }
}

void handleKey(char key) {
  if (currentState != STATE_WAITING_INPUT) return;
  
  inputPassword += key;
  printAsterisk(inputPassword.length() - 1);

  if (inputPassword.length() == 4) {
    currentState = STATE_PROCESSING; 
    delay(500);
    checkPassword();
  }
}

void checkPassword() {
  if (failedAttempts >= 3) {
    currentState = STATE_BLOCKED;
    showBlockSystem();
    startBuzzer(3000);
    failedAttempts = 0;
    delay(3000); 
  } 
  else if (inputPassword == correctPassword) {
    currentState = STATE_ACCESS_GRANTED;
    showAccessGranted();
    failedAttempts = 0;
    delay(1500);
  } 
  else {
    currentState = STATE_ACCESS_DENIED;
    showAccessDenied();
    startBuzzer(1000); 
    failedAttempts++;
    delay(1500); 
  }
  resetInput();
}

void resetInput() {
  inputPassword = "";
  if (currentState != STATE_BLOCKED) {
    currentState = STATE_WAITING_INPUT;
  }
  showWelcomeMessage();
}
