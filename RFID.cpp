#include "RFID.h"
#include "LCD.h"
#include <SPI.h>


#define RST_PIN  32    // Pin para el reset del RC522   
#define SS_PIN   53    // Pin para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Objeto para el RC522

struct TarjetaRegistrada {
  byte uid[4];  // Asumimos UIDs de 4 bytes (común en MIFARE)
  short valor;   
};

TarjetaRegistrada tarjetasConocidas[] = {
  {{0x5C, 0xF8, 0xD7, 0x73}, 2},
  {{0xF3, 0xAF, 0x2B, 0x27}, -2}  
};
const int numTarjetas = sizeof(tarjetasConocidas) / sizeof(TarjetaRegistrada);

void setupRFID() {
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Sistema RFID iniciado");
}

short readTarget() {

  if (!mfrc522.PICC_IsNewCardPresent()) {
    Serial.println("INSERTE TARJETA");
    return 0;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Error al leer la tarjeta");
    return 0;
  }

  for (int i = 0; i < numTarjetas; i++) {
    bool coincide = true;

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
      return tarjetasConocidas[i].valor;
    }
  }

  Serial.print("Tarjeta DESCONOCIDA. UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  mfrc522.PICC_HaltA();
  return 0;
}
