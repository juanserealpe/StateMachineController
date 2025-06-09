#include "RGBLed.h"

#define RED_ON_TIME 200
#define RED_OFF_TIME 100
#define RED_TOTAL_TIME 5000

bool LedOn = false;
bool redBlinking = false;

AsyncTask TaskBlink(RED_ON_TIME, true, [](){ 
    if(redBlinking) {
        if(LedOn) {
            OffRGB();
        } else {
            OnRed();
        }
    }
});
AsyncTask TaskEnd(RED_TOTAL_TIME, false, [](){
    EndBlink();
});

void setupRGB() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    OffRGB();
}

void StartRGB() {
    setupRGB();
}

void OffRGB() {
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_GREEN, 0);
    analogWrite(PIN_BLUE, 0);
    LedOn = false;
}

void ShowRGB(unsigned char red, unsigned char green, unsigned char blue) {
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN, green);
    analogWrite(PIN_BLUE, blue);
    LedOn = (red != 0 || green != 0 || blue != 0);
}

void ShowRed() { ShowRGB(255, 0, 0); }
void ShowGreen() { ShowRGB(0, 255, 0); }
void ShowBlue() { ShowRGB(0, 0, 255); }

void updateRGB() {
    TaskBlink.Update();
    TaskEnd.Update();
}

void startAlarmLed() {
    resetRGB();
    redBlinking = true;
    TaskBlink.Start();
    TaskEnd.Start();
}

void resetRGB() {
    TaskBlink.Reset();
    TaskEnd.Reset();
    redBlinking = false;
    OffRGB();
}

void EndBlink() {
    TaskBlink.Stop();
    OffRGB();
    redBlinking = false;
}

void OnRed() {
    if (!redBlinking) return;
    ShowRed();
}
