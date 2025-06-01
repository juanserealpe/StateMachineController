const int buzzerPin = 21;
unsigned long buzzerStartTime = 0;
bool buzzerActive = false;
int buzzerDuration = 0;

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void startBuzzer(int duration) {
  digitalWrite(buzzerPin, HIGH);
  buzzerStartTime = millis();
  buzzerDuration = duration;
  buzzerActive = true;
}

void updateBuzzer() {
  if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
    digitalWrite(buzzerPin, LOW);
    buzzerActive = false;
  }
}

void soundBuzzer() {
  startBuzzer(1000); // Duración de 1 segundo
}
