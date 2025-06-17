#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

/**
 * @brief Configura el módulo RFID.
 * 
 * Inicializa el lector RFID y prepara los pines necesarios.
 */
void setupRFID();

/**
 * @brief Lee el identificador del objetivo con RFID.
 * 
 * @return Identificador del objetivo leído por el módulo RFID.
 */
short readTarget();

#endif
