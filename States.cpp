#include "states.h"
#include "Logic.h"
#include <Arduino.h>

StateMachine stateMachine(NUM_STATES, 14);

Input currentInput = INPUT_NULL;
unsigned long stateEntryTime = 0;
byte stateTime = 0;

 void setupStateMachine() {
    // Transiciones desde INIT
    stateMachine.AddTransition(STATE_INIT, STATE_INIT, []() { return currentInput == INPUT_NULL; });
    stateMachine.AddTransition(STATE_INIT, STATE_MONITORING, []() { return currentInput == INPUT_CORRECT; });
    stateMachine.AddTransition(STATE_INIT, STATE_BLOCKED, []() { return currentInput == INPUT_WRONG; }); 

    // Transición desde BLOCKED
    stateMachine.AddTransition(STATE_BLOCKED, STATE_INIT, []() { return currentInput == INPUT_NULL; });
    stateMachine.AddTransition(STATE_BLOCKED, STATE_BLOCKED, []() { return currentInput == INPUT_WRONG;});  

    // Transiciones desde MONITORING
    stateMachine.AddTransition(STATE_MONITORING, STATE_MONITORING, []() { return currentInput == INPUT_CORRECT; });
    stateMachine.AddTransition(STATE_MONITORING, STATE_ALARM, []() { return currentInput == INPUT_ALARM; });
    stateMachine.AddTransition(STATE_MONITORING, STATE_PMV_HIGH, []() { return currentInput == INPUT_PMV_HIGH; });
    stateMachine.AddTransition(STATE_MONITORING, STATE_PMV_LOW, []() { return currentInput == INPUT_PMV_LOW; });
    stateMachine.AddTransition(STATE_MONITORING, STATE_BLOCKED, []() { return currentInput == INPUT_WRONG; });

    //Transiciones desde PMV_HIGH
    stateMachine.AddTransition(STATE_PMV_HIGH, STATE_PMV_HIGH, []() { return  stateTime < 7; });
    stateMachine.AddTransition(STATE_PMV_HIGH, STATE_MONITORING, []() { return stateTime > 7;  });

    //Transiciones desde PMV_LOW
    stateMachine.AddTransition(STATE_PMV_LOW, STATE_PMV_LOW, []() { return  stateTime < 4; });
    stateMachine.AddTransition(STATE_PMV_LOW, STATE_MONITORING, []() { return stateTime > 4;  });


    //Metodos controladores.
    stateMachine.SetOnEntering(STATE_INIT,onInit);
    stateMachine.SetOnEntering(STATE_MONITORING,onMonitoring);
    stateMachine.SetOnEntering(STATE_BLOCKED,onBlocked);
    stateMachine.SetOnEntering(STATE_ALARM,onAlarm);
    stateMachine.SetOnEntering(STATE_PMV_LOW,onPMVLow);
    stateMachine.SetOnEntering(STATE_PMV_HIGH,onPMVHigh);  

}

void setInitialState(State initial) {
    stateMachine.SetState(initial, false, true);
}
