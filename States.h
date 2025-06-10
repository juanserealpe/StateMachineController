/**
 * @file    States.h
 * @brief   Definición de estados y entradas para la máquina de estados del sistema.
 * @details Contiene las enumeraciones de estados, entradas y la máquina de estados principal.
 */

#ifndef STATES_H
#define STATES_H

#include <StateMachineLib.h>

/**
 * @enum State
 * @brief Estados principales del sistema
 */
enum State
{
    STATE_INIT = 0,     /**< Estado inicial del sistema */
    STATE_MONITORING,   /**< Estado de monitoreo normal */
    STATE_BLOCKED,      /**< Sistema bloqueado por seguridad */
    STATE_ALARM,        /**< Estado de alarma activada */
    STATE_PMV_HIGH,     /**< Ventilación forzada (PMV alto) */
    STATE_PMV_LOW,      /**< Ventilación reducida (PMV bajo) */
    NUM_STATES          /**< Contador de estados (no usar como estado) */
};

/**
 * @enum Input
 * @brief Entradas que provocan transiciones entre estados
 */
enum Input {
    INPUT_NULL = 0,     /**< Sin entrada/input */
    INPUT_CORRECT,      /**< Contraseña correcta ingresada */
    INPUT_WRONG,        /**< Contraseña incorrecta (incrementa intentos) */
    INPUT_RESET,        /**< Reset del sistema (tecla #) */
    INPUT_ALARM,        /**< Condición de alarma (temp > 40°C y luz < 10%) */
    INPUT_PMV_HIGH,     /**< Índice PMV > 1 (requiere ventilación) */
    INPUT_PMV_LOW,      /**< Índice PMV < -1 (led rojo) */
};

/** @brief Máquina de estados principal del sistema */
extern StateMachine stateMachine;

/** @brief Variable que almacena la última entrada procesada */
extern Input currentInput;

/**
 * @brief Configura la máquina de estados con transiciones y callbacks
 * @note Debe llamarse en setup() antes de usar la máquina de estados
 */
void setupStateMachine();

/**
 * @brief Establece el estado inicial del sistema
 * @param initial Estado inicial (usualmente STATE_INIT)
 */
void setInitialState(State initial);

#endif // STATES_H