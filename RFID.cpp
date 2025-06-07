#include <Arduino.h>
#include "RFID.h"
#include "LCD.h"
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  32    // Pin para el reset del RC522   
#define SS_PIN   53    // Pin para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Objeto para el RC522

struct TarjetaRegistrada {
  byte uid[4];  // Asumimos UIDs de 4 bytes (común en MIFARE)
  short valor;   
};

TarjetaRegistrada tarjetasConocidas[] = {
  {{0x5C, 0xF8, 0xD7, 0x73}, 0},
  {{0xF3, 0xAF, 0x2B, 0x27}, 1}  
};
const int numTarjetas = sizeof(tarjetasConocidas) / sizeof(TarjetaRegistrada);

void setupRFID() {
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Sistema RFID iniciado");
}

short readTarget() {
  // Primero verificar si hay una tarjeta presente
  if (!mfrc522.PICC_IsNewCardPresent()) {
    Serial.println("INSERTE TARJETA");
    return -5; // Código para "no hay tarjeta"
  }

  // Intentar leer la tarjeta
  if (!mfrc522.PICC_ReadCardSerial()) {
    return -5; // Error al leer la tarjeta
  }

  // Comparar con tarjetas conocidas
  for (int i = 0; i < numTarjetas; i++) {
    bool coincide = true;
    
    // Comparar byte por byte
    for (byte j = 0; j < 4; j++) {
      if (mfrc522.uid.uidByte[j] != tarjetasConocidas[i].uid[j]) {
        coincide = false;
        break;
      }
    }
    
    if (coincide) {
      Serial.print("Tarjeta reconocida. Valor: ");
      Serial.println(tarjetasConocidas[i].valor);
      mfrc522.PICC_HaltA();
      return tarjetasConocidas[i].valor; // Retorna 0 o 1
    }
  }

  mfrc522.PICC_HaltA();
  return -5; // Tarjeta no reconocida
}
void registerTarget() {
  Serial.println("Registrando tarjeta...");
}

byte readPMV() {
  return 0;
}