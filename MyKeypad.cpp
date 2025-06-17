/**
 * @file    MyKeypad.h
 * @brief   Configuración del teclado matricial para sistemas embebidos.
 * @details Define el mapeo de teclas y pines para el keypad 4x4.
 */

#ifndef MYKEYPAD_H
#define MYKEYPAD_H

#include <Keypad.h>

/** @brief Número de filas del keypad. */
const byte KEYPAD_ROWS = 4;

/** @brief Número de columnas del keypad. */
const byte KEYPAD_COLS = 4;

/**
 * @brief Mapa de caracteres del teclado.
 * @note Distribución física:
 * 1 2 3 A
 * 4 5 6 B
 * 7 8 9 C
 * * 0 # D
 */
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

/** @brief Pines Arduino conectados a las filas del keypad. */
byte rowPins[KEYPAD_ROWS] = {28, 30, 33, 34};

/** @brief Pines Arduino conectados a las columnas del keypad. */
byte colPins[KEYPAD_COLS] = {36, 38, 40, 42};

/** @brief Objeto Keypad ya configurado con el mapa y pines. */
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

/**
 * @brief Función de inicialización del keypad (reservada para futuras expansiones).
 * @note Actualmente vacía, pero proporciona un punto de extensión para configuración adicional.
 */
void setupKeypad();

#endif // MYKEYPAD_H