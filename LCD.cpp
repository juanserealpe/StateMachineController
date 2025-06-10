/**
 * @file    LCD.cpp
 * @brief   Implementación del controlador LCD para Arduino.
 * @details Maneja la visualización de mensajes en pantalla LCD con soporte para mensajes temporales y persistentes.
 */

#include "LCD.h"

// Configuración de pines LCD (RS, E, D4-D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

/** @brief Flag que indica si se está mostrando un mensaje persistente (sin temporizador). */
bool ShowingMessageWithoutTime = false;

/** @brief Flag que indica si se está mostrando un mensaje temporal (con temporizador). */
bool ShowingMessageWithTime = false;

/** 
 * @brief Tarea asincrónica para limpiar la pantalla después de MessageDuration.
 * @details Llama a RestartAllLCD() cuando se completa el temporizador.
 */
AsyncTask TaskclearLcd(MessageDuration, false, RestartAllLCD);

/**
 * @brief Inicializa la pantalla LCD con tamaño 16x2.
 * @note Se deben configurar los pines en el constructor de LiquidCrystal.
 */
void setupLCD() {
  lcd.begin(16, 2);
}

// Mensajes predefinidos ------------------------------------------------------

/**
 * @brief Muestra mensaje de bienvenida en la primera línea.
 * @details Mensaje persistente ("Ingresa clave: ").
 */
void showWelcomeMessage() {
  ShowMessage1("Ingresa clave: ");
}

/**
 * @brief Muestra mensaje de acceso concedido por 1 segundo (MessageDuration).
 */
void showAccessGranted() {
  ShowMessage("Acceso OK", MessageDuration);
}

/**
 * @brief Muestra mensaje de acceso denegado por 1 segundo (MessageDuration).
 */
void showAccessDenied() {
  ShowMessage("Clave incorrecta", MessageDuration);
}

/**
 * @brief Muestra mensaje de sistema bloqueado (persistente).
 */
void showBlockSystem() {
  ShowMessage1("Bloqueado");
}

/**
 * @brief Muestra mensaje de sistema en monitoreo (persistente).
 */
void showMonitoringSystem() {
  ShowMessage1("Monitoreando");
}

// Funciones de utilidad ------------------------------------------------------

/**
 * @brief Imprime un asterisco (*) en la posición especificada (segunda línea).
 * @param pos Posición horizontal (0-15) donde se colocará el asterisco.
 */
void printAsterisk(byte pos) {
  lcd.setCursor(pos, 1);
  lcd.print("*");
}

/**
 * @brief Muestra un mensaje temporal con temporizador personalizado.
 * @param pMessage Mensaje a mostrar.
 * @param pTime Tiempo en ms antes de limpiar (si es 0, usa MessageDuration).
 * @note Bloquea nuevos mensajes temporales hasta que se complete el temporizador.
 */
void ShowMessage(const char* pMessage, unsigned long pTime) {
  if(ShowingMessageWithTime) return;
  
  TaskclearLcd.Reset();
  TaskclearLcd.Start();
  ShowingMessageWithTime = true;
  ShowingMessageWithoutTime = false;
  ShowMessage1(pMessage);
}

/**
 * @brief Muestra un mensaje persistente (sin temporizador).
 * @param pMessage Mensaje a mostrar.
 * @note Bloquea nuevos mensajes persistentes hasta reinicio manual.
 */
void ShowMessage1(const char* pMessage) {
  if(ShowingMessageWithoutTime) return;
  
  RestartOutputLCD();
  lcd.print(pMessage);
  ShowingMessageWithoutTime = true;
}

// Funciones de reinicio ------------------------------------------------------

/**
 * @brief Reinicia la pantalla (limpia y coloca cursor en inicio).
 */
void RestartOutputLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

/**
 * @brief Reinicio completo del sistema LCD.
 * @details Limpia pantalla, detiene temporizador y reseta flags de estado.
 */
void RestartAllLCD() {
  RestartOutputLCD();
  TaskclearLcd.Reset();
  ShowingMessageWithTime = ShowingMessageWithoutTime = false;
}