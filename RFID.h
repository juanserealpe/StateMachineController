#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>


void setupRFID();
short readTarget();
void registerTarget();
byte readPMV();

#endif
