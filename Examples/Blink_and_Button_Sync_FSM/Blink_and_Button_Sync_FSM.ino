//Se va a demostrar el paralelismo

#include "FSM.h"
#define DEBUG


FSM_STATE_FUNCTION(Conf) {
  pinMode(13, OUTPUT);
}
FSM_STATE_FUNCTION(On) {
  digitalWrite(13, HIGH);
}
FSM_STATE_FUNCTION(Off) {
  digitalWrite(13, LOW);
}

FSM_STATE_FUNCTION(ConfLed) {
  pinMode(12, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}
FSM_STATE_FUNCTION(LedOn) {
  digitalWrite(12, HIGH);
}
FSM_STATE_FUNCTION(LedOff) {
  digitalWrite(12, LOW);
}

//definir estados
FSM_STATE(S0, Conf, nullptr, nullptr);
FSM_STATE(S1, On, nullptr, nullptr);
FSM_STATE(S2, Off, nullptr, nullptr);
FSM_STATE(S2_wait, nullptr, nullptr, nullptr);
FSM_STATE(S3, ConfLed, nullptr, nullptr);
FSM_STATE(S4, LedOn, nullptr, nullptr);
FSM_STATE(S5, LedOff, nullptr, nullptr);
FSM_STATE(S5_wait, nullptr, nullptr, nullptr);

//Definir condiciones
FSM_TRANSITION_CONDITION(Delay1s) {
  return from->runTime() > 1000;
}
FSM_TRANSITION_CONDITION(Delay100ms) {
  return from->runTime() > 500;
}

INSTANT

//Crear una transiccion doble desde S0 a S1 y S3
FSM_TRANSITION_MULTI(TSync, Instant, (&S2_wait, &S5_wait), (&S1, &S4));

FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, Delay1s);
FSM_TRANSITION(T2, S2, S2_wait, Delay1s);

FSM_TRANSITION(T3, S3, S4, Instant);
FSM_TRANSITION(T4, S4, S5, Delay100ms);
FSM_TRANSITION(T5, S5, S5_wait, Delay100ms);


//continuar normalmente
void setup() {
  Serial.begin(9600);
  FSM_INITIAL_STATE(S0);
  FSM_INITIAL_STATE(S3);
}

void loop() {
  FSM_RUN;
}
