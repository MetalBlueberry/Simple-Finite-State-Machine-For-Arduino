#include "FSM.h"


//Definir funciones de los estados
FSM_STATE_FUNCTION(Conf) {
  pinMode(13, OUTPUT);
}
FSM_STATE_FUNCTION(On) {
  digitalWrite(13, HIGH);
}
FSM_STATE_FUNCTION(Off) {
  digitalWrite(13, LOW);
}

//definir estados
FSM_STATE(S0, Conf, nullptr, nullptr);
FSM_STATE(S1, On, nullptr, nullptr);
FSM_STATE(S2, Off, nullptr, nullptr);

//Definir condiciones
FSM_TRANSITION_CONDITION(Delay1s) {
  return from.runTime() > 1000;
}

FSM_TRANSITION_CONDITION(Instant) {
  return true;
}

//definir transiciones
FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, Delay1s);
FSM_TRANSITION(T2, S2, S1, Delay1s);

//continuar normalmente
void setup() {
  FSM_INITIAL_STATE(S0);
}

void loop() {
  FSM_RUN

}
