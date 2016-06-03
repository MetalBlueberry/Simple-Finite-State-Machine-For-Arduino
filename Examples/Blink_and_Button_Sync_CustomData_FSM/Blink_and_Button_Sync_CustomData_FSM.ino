//Demuestra como pasar un puntero generico a los estados para utilizar los datos posteriormente de manear que permitan construir funciones genericas


#include "FSM.h"
#define DEBUG


FSM_STATE_FUNCTION(Conf) {
  pinMode(((byte*)(s->genericData))[s->id], OUTPUT);
}
FSM_STATE_FUNCTION(On) {
  digitalWrite( ((byte*)(s->genericData))[s->id], HIGH);
}
FSM_STATE_FUNCTION(Off) {
  digitalWrite(((byte*)(s->genericData))[s->id], LOW);
}

byte Config[] = {13,12,11};
//definir estados
FSM_STATE(S0, Conf, nullptr, nullptr,0, Config);
FSM_STATE(S1, On, nullptr, nullptr,0,Config);
FSM_STATE(S2, Off, nullptr, nullptr,0,Config);
FSM_STATE(S2_wait, nullptr, nullptr, nullptr,0,Config);

FSM_STATE(S3, Conf, nullptr, nullptr,1,Config);
FSM_STATE(S4, On, nullptr, nullptr,1,Config);
FSM_STATE(S5, Off, nullptr, nullptr,1,Config);
FSM_STATE(S5_wait, nullptr, nullptr, nullptr,1,Config);

FSM_STATE(S6, Conf, nullptr, nullptr,2,Config);
FSM_STATE(S7, On, nullptr, nullptr,2,Config);
FSM_STATE(S8, Off, nullptr, nullptr,2,Config);
FSM_STATE(S8_wait, nullptr, nullptr, nullptr,2,Config);

//Definir condiciones
FSM_TRANSITION_CONDITION(Delay1s) {
  return from->runTime() > 1000;
}
FSM_TRANSITION_CONDITION(Delay100ms) {
  return from->runTime() > 100;
}
FSM_TRANSITION_CONDITION(Delay300ms) {
  return from->runTime() > 300;
}

INSTANT

//Crear una transiccion doble desde S0 a S1 y S3
FSM_TRANSITION_MULTI(TSync, Instant, (&S2_wait, &S5_wait, &S8_wait), (&S1, &S4 , &S7));

FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, Delay1s);
FSM_TRANSITION(T2, S2, S2_wait, Delay1s);

FSM_TRANSITION(T3, S3, S4, Instant);
FSM_TRANSITION(T4, S4, S5, Delay100ms);
FSM_TRANSITION(T5, S5, S5_wait, Delay100ms);

FSM_TRANSITION(T6, S6, S7, Instant);
FSM_TRANSITION(T7, S7, S8, Delay300ms);
FSM_TRANSITION(T8, S8, S8_wait, Delay300ms);


//continuar normalmente
void setup() {
  FSM_INITIAL_STATE(S0);
  FSM_INITIAL_STATE(S3);
  FSM_INITIAL_STATE(S6);
}

void loop() {
  FSM_RUN;
}

