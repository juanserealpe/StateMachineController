#include "RGBLed.h"

// Variables para almacenar los tiempos actuales
unsigned int currentRedOnTime = 200;    ///< Tiempo de encendido por defecto del LED rojo.
unsigned int currentRedOffTime = 100;   ///< Tiempo de apagado por defecto del LED rojo.
unsigned int currentRedTotalTime = 5000; ///< Duración total por defecto de la alarma LED.
bool ledBucleActive = false; ///< Indica si el bucle del LED está activo.
int currentBucleMode = 0; ///< Modo actual del bucle del LED (0=inactivo, 1=activo).

bool LedOn = false; ///< Indica si el LED está encendido.
bool redBlinking = false; ///< Indica si el LED rojo está parpadeando.

// Declaración adelantada de las tareas
/**
 * @brief Tarea de parpadeo del LED.
 */
AsyncTask TaskBlink(currentRedOnTime, true, nullptr);

/**
 * @brief Tarea que controla el tiempo total de parpadeo del LED rojo.
 */
AsyncTask TaskEnd(currentRedTotalTime, false, nullptr);

/**
 * @brief Configura los pines del LED RGB y inicializa las tareas de parpadeo.
 */
void setupRGB() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    OffRGB();
    
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

/**
 * @brief Inicializa el LED RGB.
 */
void StartRGB() {
    setupRGB();
}

/**
 * @brief Apaga el LED RGB.
 */
void OffRGB() {
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_GREEN, 0);
    analogWrite(PIN_BLUE, 0);
    LedOn = false;
}

/**
 * @brief Muestra un color RGB específico.
 * 
 * @param red Nivel de intensidad del rojo (0-255).
 * @param green Nivel de intensidad del verde (0-255).
 * @param blue Nivel de intensidad del azul (0-255).
 */
void ShowRGB(unsigned char red, unsigned char green, unsigned char blue) {
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN, green);
    analogWrite(PIN_BLUE, blue);
    LedOn = (red != 0 || green != 0 || blue != 0);
}

/**
 * @brief Enciende el LED en rojo.
 */
void ShowRed() { ShowRGB(255, 0, 0); }

/**
 * @brief Enciende el LED en verde.
 */
void ShowGreen() { ShowRGB(0, 255, 0); }

/**
 * @brief Enciende el LED en azul.
 */
void ShowBlue() { ShowRGB(0, 0, 255); }

/**
 * @brief Actualiza el estado de las tareas del LED RGB.
 */
void updateRGB() {
    TaskBlink.Update();
    TaskEnd.Update();
}

/**
 * @brief Inicia una secuencia de alarma con el LED RGB.
 * 
 * @param onTime Tiempo de encendido en milisegundos.
 * @param offTime Tiempo de apagado en milisegundos.
 * @param totalTime Duración total de la alarma en milisegundos.
 */
void startAlarmLed(unsigned int onTime = 200, unsigned int offTime = 100, unsigned int totalTime = 5000) {
    resetRGB();
    
    currentRedOnTime = onTime;
    currentRedOffTime = offTime;
    currentRedTotalTime = totalTime;
    
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

/**
 * @brief Inicia o detiene un bucle infinito del LED rojo.
 * 
 * @param prmNum Si es 0, inicia el bucle. Si es 1, lo detiene.
 */
void startBucleLed(int prmNum) {
    if(prmNum == 0) {
        if(ledBucleActive) return;
        
        resetRGB();
        ledBucleActive = true;
        currentBucleMode = 0;

        TaskBlink = AsyncTask(currentRedOnTime, true, [](){ 
            if(redBlinking && ledBucleActive) {
                LedOn ? OffRGB() : OnRed();
            }
        });

        redBlinking = true;
        TaskBlink.Start();
    }
    else if(prmNum == 1) {
        ledBucleActive = false;
        redBlinking = false;
        TaskBlink.Stop();
        OffRGB();
    }
}

/**
 * @brief Reinicia el estado del LED RGB.
 */
void resetRGB() {
    TaskBlink.Stop();
    TaskEnd.Stop();
    redBlinking = false;
    OffRGB();
}

/**
 * @brief Finaliza la animación de parpadeo del LED.
 */
void EndBlink() {
    TaskBlink.Stop();
    OffRGB();
    redBlinking = false;
}

/**
 * @brief Enciende el LED en rojo si está en modo parpadeo.
 */
void OnRed() {
    if (!redBlinking) return;
    ShowRed();
}

/**
 * @brief Detiene la alarma del LED.
 */
void stopAlarmLed() {
    TaskBlink.Stop();
    TaskEnd.Stop();
    redBlinking = false;
    OffRGB();
}
