#include "RFID.h"
#include "LCD.h"
#include <SPI.h>

#define RST_PIN  32    ///< Pin para el reset del RC522   
#define SS_PIN   53    ///< Pin para el SS (SDA) del RC522

/**
 * @brief Objeto para el manejo del módulo RFID RC522.
 */
MFRC522 mfrc522(SS_PIN, RST_PIN);

/**
 * @struct TarjetaRegistrada
 * @brief Estructura que almacena el UID y el valor asociado de una tarjeta RFID.
 */
struct TarjetaRegistrada {
  byte uid[4];  ///< UID de la tarjeta RFID (asumimos UIDs de 4 bytes).
  short valor;  ///< Valor asociado a la tarjeta.
};

/**
 * @brief Lista de tarjetas RFID registradas con sus valores asociados.
 */
TarjetaRegistrada tarjetasConocidas[] = {
  {{0x5C, 0xF8, 0xD7, 0x73}, 2},
  {{0xF3, 0xAF, 0x2B, 0x27}, -2}  
};

/**
 * @brief Cantidad de tarjetas registradas en el sistema.
 */
const int numTarjetas = sizeof(tarjetasConocidas) / sizeof(TarjetaRegistrada);

/**
 * @brief Inicializa el módulo RFID.
 * 
 * Configura el lector RFID y muestra un mensaje de inicio en la consola serie.
 */
void setupRFID() {
  mfrc522.PCD_Init(); ///< Inicializa el módulo RC522
}

/**
 * @brief Lee una tarjeta RFID y devuelve su valor si está registrada.
 * 
 * @return Valor asociado a la tarjeta si está registrada, 0 si no se reconoce o hay un error.
 */
short readTarget() {
  if (!mfrc522.PICC_IsNewCardPresent()) return 0;
  if (!mfrc522.PICC_ReadCardSerial()) return 0;
  for (int i = 0; i < numTarjetas; i++) {
    bool coincide = true;
    for (byte j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != tarjetasConocidas[i].uid[j]) {
        coincide = false;
        break;
      }
    }
    if (coincide) {
      mfrc522.PICC_HaltA();
      return tarjetasConocidas[i].valor;
    }
  }  
  mfrc522.PICC_HaltA();
  return 0;
}
