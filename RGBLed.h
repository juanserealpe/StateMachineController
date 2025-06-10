#ifndef RGBLed_H
#define RGBLed_H

#include <Arduino.h>
#include "AsyncTaskLib.h"

#define PIN_RED 8    ///< Pin para el LED rojo.
#define PIN_GREEN 9  ///< Pin para el LED verde.
#define PIN_BLUE 10  ///< Pin para el LED azul.

/**
 * @brief Muestra un color RGB específico.
 * 
 * @param red Nivel de intensidad del rojo (0-255).
 * @param green Nivel de intensidad del verde (0-255).
 * @param blue Nivel de intensidad del azul (0-255).
 */
void ShowRGB(unsigned char red, unsigned char green, unsigned char blue);

/**
 * @brief Enciende el LED en rojo.
 */
void ShowRed();

/**
 * @brief Enciende el LED en verde.
 */
void ShowGreen();

/**
 * @brief Enciende el LED en azul.
 */
void ShowBlue();

/**
 * @brief Inicia el bucle de parpadeo del LED.
 * 
 * @param prmNum Número de repeticiones del parpadeo.
 */
void startBucleLed(int prmNum);

/**
 * @brief Enciende el LED RGB.
 */
void StartRGB();

/**
 * @brief Apaga el LED RGB.
 */
void OffRGB();

/**
 * @brief Configura los pines del LED RGB.
 */
void setupRGB();

/**
 * @brief Actualiza el estado del LED RGB.
 */
void updateRGB();

/**
 * @brief Detiene la alarma del LED.
 */
void stopAlarmLed();

/**
 * @brief Inicia una secuencia de alarma con el LED RGB.
 * 
 * @param onTime Tiempo en milisegundos que permanece encendido.
 * @param offTime Tiempo en milisegundos que permanece apagado.
 * @param totalTime Duración total de la alarma en milisegundos.
 */
void startAlarmLed(unsigned int onTime = 200, unsigned int offTime = 100, unsigned int totalTime = 5000);

/**
 * @brief Reinicia el estado del LED RGB.
 */
void resetRGB();

/**
 * @brief Finaliza la animación de parpadeo del LED.
 */
void EndBlink();

/**
 * @brief Enciende el LED en rojo.
 */
void OnRed();

#endif
