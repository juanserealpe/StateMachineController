/**
 * @file    LCD.h
 * @brief   Controlador de pantalla LCD para Arduino.
 * @details Proporciona funciones para mostrar mensajes y estados del sistema.
 */

#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>
#include <Arduino.h>
#include <AsyncTaskLib.h>

/** @brief Duración predeterminada (ms) para mostrar mensajes temporales. */
#define MessageDuration 1000

/** @brief Objeto LiquidCrystal para controlar la pantalla LCD. */
extern LiquidCrystal lcd;

/** @brief Tarea asincrónica para limpiar la pantalla LCD después de un tiempo. */
extern AsyncTask TaskclearLcd;

/**
 * @brief Inicializa la pantalla LCD con los ajustes básicos.
 * @note Debe llamarse en setup().
 */
void setupLCD();

// Mensajes predefinidos
/**
 * @brief Muestra un mensaje de bienvenida en la pantalla.
 */
void showWelcomeMessage();

/**
 * @brief Muestra un mensaje de acceso concedido.
 */
void showAccessGranted();

/**
 * @brief Muestra un mensaje de acceso denegado.
 */
void showAccessDenied();

/**
 * @brief Muestra un mensaje de sistema bloqueado.
 */
void showBlockSystem();

/**
 * @brief Muestra un mensaje de sistema en modo monitoreo.
 */
void showMonitoringSystem();

// Funciones de utilidad
/**
 * @brief Imprime un asterisco en la posición especificada.
 * @param pos Posición del carácter en la pantalla (0-indexado).
 */
void printAsterisk(byte pos);

/**
 * @brief Muestra un mensaje personalizado con temporizador opcional.
 * @param pMessage Mensaje a mostrar (cadena de caracteres).
 * @param pTime Tiempo en ms antes de limpiar la pantalla (0 = usar MessageDuration).
 */
void ShowMessage(const char* pMessage, unsigned long pTime = 0);

/**
 * @brief Muestra un mensaje en la primera línea de la LCD (sin temporizador).
 * @param pMessage Mensaje a mostrar.
 */
void ShowMessage1(const char* pMessage);

// Funciones de reinicio
/**
 * @brief Reinicia la salida de la pantalla (limpia y vuelve al estado inicial).
 */
void RestartOutputLCD();

/**
 * @brief Reinicia completamente el estado de la pantalla LCD.
 */
void RestartAllLCD();

#endif // LCD_H