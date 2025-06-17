/**
 * @file    Logic.h
 * @brief   Lógica principal del sistema de seguridad con Arduino.
 * @details Maneja estados del sistema, lectura de sensores y validación de contraseña.
 */

#ifndef LOGIC_H
#define LOGIC_H

#include <DHT.h>
#include <Arduino.h>
#include <Keypad.h>
#include <AsyncTaskLib.h>
#include "states.h"

// Configuración de hardware ------------------------------------------------

/** @brief Pin digital conectado al sensor DHT11. */
#define DHTPIN 22  

/** @brief Tipo de sensor DHT (DHT11 en este caso). */
#define DHTTYPE DHT11

/** @brief Pin analógico para el fotoresistor (lectura de luz ambiental). */
#define PIN_FOTORESISTOR A0

/** @brief Pin digital para controlar el relé del ventilador. */
#define RELAY_FAN 46

// Variables globales (externas) --------------------------------------------

extern DHT dht;                     /**< @brief Objeto para el sensor DHT11. */
extern int alarmCount;              /**< @brief Contador de activaciones de alarma. */
extern byte indx;                   /**< @brief Índice para operaciones internas. */
extern char key;                    /**< @brief Tecla presionada en el keypad. */
extern byte inputIndex;             /**< @brief Índice de entrada de contraseña. */
extern byte failedAttempts;         /**< @brief Intentos fallidos de contraseña. */
extern char inputPassword[];        /**< @brief Buffer para almacenar la contraseña ingresada. */
extern char correctPassword[];      /**< @brief Contraseña correcta del sistema. */
extern int CurrentLightValue;       /**< @brief Valor actual de luz ambiental. */
extern float CurrentTemperature;    /**< @brief Temperatura actual leída por DHT11. */
extern float Currenthumidity;       /**< @brief Humedad actual leída por DHT11. */

/** @brief Tarea asincrónica para manejar timeouts del sistema. */
extern AsyncTask TaskTimeOut;

// Funciones principales ---------------------------------------------------

/**
 * @brief Lee una tecla del keypad.
 * @return true si se presionó una tecla, false en caso contrario.
 */
bool readKeypad();

/**
 * @brief Procesa la tecla presionada (almacena en buffer o ejecuta acciones).
 */
void handleKey();

/**
 * @brief Compara dos cadenas de caracteres.
 * @param pChar1 Primera cadena a comparar.
 * @param pChar2 Segunda cadena a comparar.
 * @return true si son iguales, false en caso contrario.
 */
bool Equals(char* pChar1, char* pChar2);

/**
 * @brief Verifica si la contraseña ingresada es correcta.
 * @details Incrementa failedAttempts si es incorrecta y bloquea el sistema tras 3 intentos.
 */
void checkPassword();

/**
 * @brief Ejecuta acciones cuando la contraseña es incorrecta.
 */
void incorrectPassword();

// Controladores de estados ------------------------------------------------

/**
 * @brief Estado inicial del sistema (configuración inicial).
 */
void onInit();

/**
 * @brief Estado de monitoreo activo (lectura de sensores).
 */
void onMonitoring();

/**
 * @brief Estado de sistema bloqueado (tras múltiples intentos fallidos).
 */
void onBlocked();

/**
 * @brief Estado de alarma activada.
 */
void onAlarm();

/**
 * @brief Estado de alta temperatura/ventilación forzada.
 */
void onPMVHigh();

/**
 * @brief Estado de baja temperatura/ventilación desactivada.
 */
void onPMVLow();

// Transiciones de estado --------------------------------------------------

/**
 * @brief Cambia el estado actual del sistema.
 * @param newInput Nuevo estado a activar (ver enumeración en states.h).
 */
void changeState(Input newInput);

// Funciones de reinicio --------------------------------------------------

/**
 * @brief Limpia el buffer de contraseña ingresada.
 */
void ResetPassword();

/**
 * @brief Reinicia variables temporales del sistema.
 */
void ResetVars();

/**
 * @brief Reinicio completo del sistema (variables y hardware).
 */
void ResetAll();

#endif // LOGIC_H