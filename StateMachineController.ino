/**
 * @file    SecureSystem.ino
 * @brief   Sistema de seguridad con Arduino basado en máquina de estados.
 * @details Integra:
 * - Control por keypad/RFID
 * - Monitoreo de temperatura/humedad
 * - Pantalla LCD
 * - Buzzer de alarma
 * - Ventilación automática
 * @author  [Tu Nombre]
 * @date    [Fecha de creación]
 * @version 1.0
 */

#include "States.h"
#include "Logic.h"
#include "LCD.h"  
#include "Buzzer.h"
#include "MyKeypad.h"
#include "TemperatureSensor.h"
#include "RGBLed.h"
#include "RFID.h"

// Configuración inicial ====================================================

/**
 * @brief Inicialización de hardware y módulos.
 * @note Se ejecuta una vez al iniciar el dispositivo.
 */
void setup() {
  Serial.begin(9600);  // Inicia comunicación serial para debugging

  // Configuración de periféricos
  setupBuzzer();       // Inicializa buzzer
  setupStateMachine(); // Configura máquina de estados
  setupLCD();          // Inicia pantalla LCD
  setupRFID();         // Configura lector RFID
  setupRGB();          // Inicializa LED RGB
  setupTemperature();  // Configura sensor de temperatura

  dht.begin();         // Inicia sensor DHT
  pinMode(RELAY_FAN, OUTPUT);  // Configura pin del ventilador como salida
  digitalWrite(RELAY_FAN, LOW);
}

// Bucle principal =========================================================

/**
 * @brief Bucle de ejecución continua.
 * @details Actualiza:
 * - Máquina de estados principal
 * - Temporizador de LCD
 * - Temporizador general
 * - Estado del LED RGB
 * - Sonido del buzzer
 */
void loop() {
  stateMachine.Update();    // Actualiza lógica del sistema
  TaskclearLcd.Update();    // Maneja limpieza automática de LCD
  TaskTimeOut.Update();     // Actualiza temporizador global
  updateRGB();              // Refresca estado del LED
  updateBuzzer();           // Gestiona patrones de sonido
}