#include "RGBLed.h"

// Variables para almacenar los tiempos actuales
unsigned int currentRedOnTime = 200;    // Valores por defecto
unsigned int currentRedOffTime = 100;
unsigned int currentRedTotalTime = 5000;
bool ledBucleActive = false;
int currentBucleMode = 0; // 0=inactivo, 1=activo


bool LedOn = false;
bool redBlinking = false;

// Declaración adelantada de las tareas
AsyncTask TaskBlink(currentRedOnTime, true, nullptr);
AsyncTask TaskEnd(currentRedTotalTime, false, nullptr);

void setupRGB() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    OffRGB();
    
    // Reasignar las lambdas después de la inicialización
    TaskBlink = AsyncTask(currentRedOnTime, true, [](){ 
        if(redBlinking) {
            if(LedOn) {
                OffRGB();
            } else {
                OnRed();
            }
        }
    });
    
    TaskEnd = AsyncTask(currentRedTotalTime, false, [](){
        EndBlink();
    });
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

// Versión modificada de startAlarmLed con parámetros
void startAlarmLed(unsigned int onTime = 200, unsigned int offTime = 100, unsigned int totalTime = 5000) {
    resetRGB();
    
    // Actualizar los tiempos
    currentRedOnTime = onTime;
    currentRedOffTime = offTime;
    currentRedTotalTime = totalTime;
    
    // Recrear las tareas con los nuevos tiempos
    TaskBlink = AsyncTask(currentRedOnTime, true, [](){ 
        if(redBlinking) {
            if(LedOn) {
                OffRGB();
            } else {
                OnRed();
            }
        }
    });
    
    TaskEnd = AsyncTask(currentRedTotalTime, false, [](){
        EndBlink();
    });
    
    redBlinking = true;
    TaskBlink.Start();
    TaskEnd.Start();
}

void startBucleLed(int prmNum) {
    if(prmNum == 0) {
        // Iniciar bucle infinito
        if(ledBucleActive) return; // Ya está activo
        
        resetRGB();
        ledBucleActive = true;
        currentBucleMode = 0;
        
        // Configurar tarea de parpadeo sin tiempo total
        TaskBlink = AsyncTask(currentRedOnTime, true, [](){ 
            if(redBlinking && ledBucleActive) {
                LedOn ? OffRGB() : OnRed();
            }
        });
        
        redBlinking = true;
        TaskBlink.Start();
    }
    else if(prmNum == 1) {
        // Detener bucle
        ledBucleActive = false;
        redBlinking = false;
        TaskBlink.Stop();
        OffRGB();
    }
}

void resetRGB() {
    TaskBlink.Stop();
    TaskEnd.Stop();
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
void stopAlarmLed() {
    TaskBlink.Stop();
    TaskEnd.Stop();
    redBlinking = false;
    OffRGB();
}
