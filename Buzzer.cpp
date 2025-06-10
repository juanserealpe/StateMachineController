/**
 * @file    Buzzer.cpp
 * @brief   Implementación del controlador del buzzer para Arduino.
 * @details Maneja patrones de sonido intermitente mediante tareas asincrónicas.
 */

#include "Buzzer.h"

/** @brief Tiempo en milisegundos que el buzzer permanece encendido en modo alarma. */
#define TimeOnAlarm 200

/** @brief Tiempo en milisegundos que el buzzer permanece apagado en modo alarma. */
#define TimeOffAlarm 100

AsyncTask TaskBuzzerONAlarm(TimeOnAlarm, false, OnBuzzer); /**< @brief Tarea para encender el buzzer. */
AsyncTask TaskBuzzerOFFAlarm(TimeOffAlarm, false, OffBuzzer); /**< @brief Tarea para apagar el buzzer. */

/** @brief Flag que indica si el buzzer está activo (true/false). */
bool buzzerActive = false;

/**
 * @brief Configura el pin del buzzer como salida y lo inicializa apagado.
 * @note Debe llamarse en el setup() principal.
 */
void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

/**
 * @brief Actualiza el estado de las tareas del buzzer (para modo alarma intermitente).
 * @note Debe llamarse en el loop() principal.
 */
void updateBuzzer(){
  TaskBuzzerONAlarm.Update();
  TaskBuzzerOFFAlarm.Update();
}

/**
 * @brief Activa el modo alarma del buzzer (patrón intermitente).
 * @details Enciende el buzzer y programa las tareas para alternar entre estados HIGH/LOW.
 * Si el buzzer ya está activo, no realiza cambios.
 */
void startBuzzer(){
  if(buzzerActive) return;
  
  buzzerActive = true;
  digitalWrite(buzzerPin, HIGH);
  TaskBuzzerONAlarm.SetIntervalMillis(TimeOnAlarm);
  TaskBuzzerOFFAlarm.SetIntervalMillis(TimeOffAlarm);
  TaskBuzzerONAlarm.Start();
  TaskBuzzerOFFAlarm.Start();
}

/**
 * @brief Detiene el buzzer y reinicia todas las tareas asociadas.
 */
void resetBuzzer(){
  TaskBuzzerONAlarm.Stop();
  TaskBuzzerOFFAlarm.Stop();
  digitalWrite(buzzerPin, LOW);
  buzzerActive = false;
}

/**
 * @brief Apaga el buzzer inmediatamente (alias de resetBuzzer()).
 */
void stopBuzzer(){
  resetBuzzer(); 
}

/**
 * @brief Enciende el buzzer manualmente e inicia la tarea de apagado.
 */
void OnBuzzer(){
  digitalWrite(buzzerPin, HIGH);
  TaskBuzzerOFFAlarm.Start();
}

/**
 * @brief Apaga el buzzer manualmente e inicia la tarea de encendido.
 */
void OffBuzzer(){
  digitalWrite(buzzerPin, LOW);
  TaskBuzzerONAlarm.Start();
}