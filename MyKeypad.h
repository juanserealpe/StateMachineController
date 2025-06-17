/**
 * @file    MyKeypad.h
 * @brief   Interfaz para el control del teclado matricial en Arduino.
 * @details Proporciona la declaración del objeto Keypad y función de inicialización.
 */

#ifndef MYKEYPAD_H
#define MYKEYPAD_H

#include <Arduino.h>
#include <Keypad.h>

/** 
 * @brief Objeto Keypad externo para uso en otros módulos.
 * @note La configuración concreta (pines y teclas) se realiza en MyKeypad.cpp.
 */
extern Keypad keypad;

/**
 * @brief Inicializa la configuración del teclado matricial.
 * @details Debe llamarse durante el setup() principal. Actualmente implementada como
 *          función vacía para futura expansión (ej: ajuste de tiempo debounce).
 */
void setupKeypad();

#endif // MYKEYPAD_H