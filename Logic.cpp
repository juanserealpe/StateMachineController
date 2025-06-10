/**
 * @file    Logic.cpp
 * @brief   Implementación de la lógica principal del sistema de seguridad.
 * @details Contiene la implementación de las funciones declaradas en Logic.h.
 * @author  [Tu Nombre]
 * @date    [Fecha de creación o modificación]
 */

#include "Arduino.h"
#include "HardwareSerial.h"
#include "Logic.h"
#include "LCD.h" 
#include "MyKeypad.h" 
#include "RGBLed.h"
#include "RFID.h"
#include "Buzzer.h"
#include "states.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"

/** @brief Tamaño del array para contraseñas. */
#define ARRAY_SIZE 4

/** @brief Objeto DHT para lectura de temperatura y humedad. */
DHT dht(DHTPIN, DHTTYPE);

// Prototipos de funciones locales
void TimeOut();
void ReadSensors();

// Variables globales
unsigned long currentTimeOut = 0;    /**< @brief Tiempo de espera actual para timeout. */
int alarmCount = 0;                  /**< @brief Contador de activaciones de alarma. */
char key;                            /**< @brief Tecla actual presionada en el keypad. */
bool fromAlarm = false;              /**< @brief Flag que indica si se viene del estado de alarma. */
byte inputIndex = 0;                 /**< @brief Índice actual para entrada de contraseña. */
byte failedAttempts = 0;             /**< @brief Contador de intentos fallidos de contraseña. */
char inputPassword[] = "****";       /**< @brief Buffer para almacenar la contraseña ingresada. */
char correctPassword[] = "1234";     /**< @brief Contraseña correcta del sistema. */
int CurrentLightValue = 0;           /**< @brief Valor actual de luz ambiental. */
float CurrentTemperature = 0;        /**< @brief Temperatura actual leída por el sensor. */
float Currenthumidity = 0;           /**< @brief Humedad actual leída por el sensor. */
short varTargetValue = 0;            /**< @brief Pmv actual leída por el RFID. */

/** @brief Tarea asincrónica para manejar timeouts del sistema. */
AsyncTask TaskTimeOut(currentTimeOut, false, TimeOut);

/** @brief Tarea asincrónica para lectura periódica de sensores. */
AsyncTask TaskReadSensors(3000, false, ReadSensors);

/**
 * @brief Lee los valores de los sensores y los muestra en el LCD.
 */
void ReadSensors(){
  CurrentLightValue = analogRead(PIN_FOTORESISTOR);
  Currenthumidity = dht.readHumidity();
  CurrentTemperature = dht.readTemperature();
  lcd.clear();
  
  lcd.setCursor(0, 0);   
  lcd.print("H:"); 
  if(Currenthumidity < 10) lcd.print("0");
  lcd.print(Currenthumidity);
  lcd.print("% ");
  
  lcd.print("L:");
  if(CurrentLightValue < 10) lcd.print("0");
  lcd.print(CurrentLightValue);
  lcd.print("%");

  lcd.setCursor(0, 1); 
  lcd.print("T:");
  if(CurrentTemperature < 10) lcd.print("0");
  lcd.print(CurrentTemperature);
  lcd.print(" C");
  varTargetValue = readTarget();
}

/**
 * @brief Lee una tecla del keypad.
 * @return true si se presionó una tecla, false en caso contrario.
 */
bool readKeypad() {
  key = keypad.getKey();
  return (key != NO_KEY);
}

/**
 * @brief Procesa la tecla presionada en el keypad.
 */
void handleKey() {
  if(key == '#') checkPassword();
  else {
    printAsterisk(inputIndex);
    if(inputIndex < 4) { inputPassword[inputIndex] = key; }
    inputIndex++;
  }
}

/**
 * @brief Compara dos cadenas de caracteres.
 * @param pChar1 Primera cadena a comparar.
 * @param pChar2 Segunda cadena a comparar.
 * @return true si son iguales, false en caso contrario.
 */
bool Equals(char* pChar1, char* pChar2) {
  return (memcmp(pChar1, pChar2, ARRAY_SIZE) == 0);
}

/**
 * @brief Verifica si la contraseña ingresada es correcta.
 */
void checkPassword() {
  if(Equals(inputPassword, correctPassword)){
    showAccessGranted();
    changeState(INPUT_CORRECT);
  }
  else incorrectPassword();
}

/**
 * @brief Maneja un intento fallido de contraseña.
 */
void incorrectPassword(){
  showAccessDenied();
  failedAttempts++;
  ResetVars();
  ResetPassword();
}

/**
 * @brief Estado inicial del sistema.
 */
void onInit() {
  showWelcomeMessage();
  if(failedAttempts == 3) changeState(INPUT_WRONG);
  else { if(readKeypad()) handleKey(); }
}

/**
 * @brief Estado de sistema bloqueado.
 */
void onBlocked(){
  startBucleLed(0);
  showBlockSystem();
  if(readKeypad()) { 
    if(key == '#') {
      startBucleLed(1);
      changeState(INPUT_NULL);  
    }
  }
}

/**
 * @brief Estado de monitoreo activo.
 */
void onMonitoring(){
  digitalWrite(RELAY_FAN, HIGH);
  if(!TaskReadSensors.IsActive()) TaskReadSensors.Start();
  else showMonitoringSystem();
  TaskReadSensors.Update();
  resetRGB();
  OffRGB();
  if(LightValue < 10 && currentTemperature > 40.0){
    changeState(INPUT_ALARM);
  }
  if(varTargetValue > 1) {
    changeState(INPUT_PMV_HIGH);
    //changeState(INPUT_ALARM);
  }
  else {
    if(varTargetValue < -1) {changeState(INPUT_PMV_LOW);}
  }
}

/**
 * @brief Estado de alarma activada.
 */
void onAlarm(){ 
  startBucleLed(0);
  fromAlarm = true;

  if(!TaskTimeOut.IsActive()){ 
    TaskTimeOut.SetIntervalMillis(5000); 
    TaskTimeOut.Start(); 
    stopBuzzer(); 
    startBucleLed(1);
  } 
  if(!buzzerActive) startBuzzer(); 
  updateBuzzer(); 
  ShowMessage1("En alarma");
} 

/**
 * @brief Estado de alta temperatura/ventilación forzada.
 */
void onPMVHigh(){
  digitalWrite(RELAY_FAN, LOW);
  resetRGB();
  OffRGB();
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(7000);
    TaskTimeOut.Start();
    RestartAllLCD();
  }  
  ShowMessage1("En PmVHigh");
}

/**
 * @brief Estado de baja temperatura/ventilación desactivada.
 */
void onPMVLow(){
  if(!TaskTimeOut.IsActive()){
    TaskTimeOut.SetIntervalMillis(4000);
    TaskTimeOut.Start();
    RestartAllLCD();
  } 
  ShowMessage1("En PmVLow");
  resetRGB(); 
  ShowRed(); 
}

/**
 * @brief Cambia el estado actual del sistema.
 * @param newInput Nuevo estado a activar.
 */
void changeState(Input newInput){
  currentInput = newInput;
  ResetAll();
}

/**
 * @brief Función de callback para el timeout del sistema.
 */
void TimeOut(){
  if(fromAlarm) alarmCount++;
  else alarmCount = 0;
  fromAlarm = false;   
  if(alarmCount >= 3) { 
    alarmCount = 0; 
    resetBuzzer(); 
    changeState(INPUT_WRONG); 
    return;
  } 
  changeState(INPUT_CORRECT);
}

/**
 * @brief Reinicia el buffer de contraseña.
 */
void ResetPassword(){
  for (byte idx = 0; idx < ARRAY_SIZE; idx++) inputPassword[idx] = '*';   
}

/**
 * @brief Reinicia variables temporales del sistema.
 */
void ResetVars(){
  inputIndex = key = 0;
  fromAlarm = false;
}

/**
 * @brief Reinicio completo del sistema.
 */
void ResetAll(){
  failedAttempts = varTargetValue = 0;
  TaskReadSensors.Stop();
  TaskReadSensors.Reset();
  resetBuzzer(); 
  TaskTimeOut.Reset();
  RestartAllLCD();
  ResetPassword(); 
  ResetVars();
}