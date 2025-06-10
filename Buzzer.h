/**
 * @file    Buzzer.h
 * @brief   Controlador del buzzer para Arduino (activación/desactivación y patrones de sonido).
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include <AsyncTaskLib.h>

/** @brief Pin digital conectado al buzzer. */
#define buzzerPin 13

/** @brief Flag que indica si el buzzer está activo (true/false). */
extern bool buzzerActive;

/** @brief Tiempo en milisegundos que el buzzer permanece encendido en modo alarma. */
#define TimeOnAlarm 200

/** @brief Tiempo en milisegundos que el buzzer permanece apagado en modo alarma. */
#define TimeOffAlarm 100

/**
 * @brief Configura el pin del buzzer como salida (debe llamarse en setup()).
 */
void setupBuzzer();

/**
 * @brief Actualiza el estado del buzzer (debe llamarse en loop() para patrones repetitivos).
 */
void updateBuzzer();

/**
 * @brief Activa el buzzer en modo alarma (intermitente según TimeOnAlarm/TimeOffAlarm).
 */
void startBuzzer();

/**
 * @brief Detiene el buzzer y reinicia su estado interno.
 */
void resetBuzzer();

/**
 * @brief Apaga el buzzer inmediatamente (sin reiniciar estado).
 */
void stopBuzzer();

/**
 * @brief Enciende el buzzer de forma manual (estado constante).
 */
void OnBuzzer();

/**
 * @brief Apaga el buzzer de forma manual (estado constante).
 */
void OffBuzzer();

#endif // BUZZER_H