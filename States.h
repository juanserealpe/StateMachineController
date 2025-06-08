#ifndef STATES_H
#define STATES_H
#include <StateMachineLib.h>

enum State
{
    STATE_INIT = 0,
    STATE_MONITORING,
    STATE_BLOCKED,
    STATE_ALARM,
    STATE_PMV_HIGH,
    STATE_PMV_LOW,
    NUM_STATES
};
enum Input {
    INPUT_NULL = 0,     // Sin input
    INPUT_CORRECT,      // Contraseña correcta
    INPUT_WRONG,        // Contraseña incorrecta (intentos++)
    INPUT_RESET,        // Resetear bloqueo(#)
    INPUT_ALARM,        // Condición de alarma (temp > 40 y luz < 10)
    INPUT_PMV_HIGH,     // PMV > 1
    INPUT_PMV_LOW,      // PMV < -1
};

extern StateMachine stateMachine;
extern Input currentInput;
extern unsigned long stateTime;

void setupStateMachine();
void setInitialState(State initial); 
void updateTimeExecute();
void startTime();
void restartTimes();
#endif
