#include "TemperatureSensor.h"
#include "LCD.h"  
#include <OneWire.h>
#include <DallasTemperature.h>
// === Configuración del sensor ===
#define ONE_WIRE_BUS 20 // Pin del sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float currentTemperature = 0.0;

void setupTemperature() {
  sensors.begin(); // Inicializa el sensor DS18B20
}
void updateTemperature() {
  sensors.requestTemperatures();
  currentTemperature = sensors.getTempCByIndex(0);

  lcd.setCursor(0, 1); // Línea 2
  lcd.print("Temp: ");
  lcd.print(currentTemperature, 1); // Un decimal
  lcd.print((char)223); // Grado °
  lcd.print("C   ");
}
