/**************************************************
  Autor: Víctor Pérez Domingo
  Fecha: 12/05/2016

  A Button on pin 2 controls the state of pin 12
  Pin 13 blinks independently
*************************************************/

//Include the library
#include <FSM.h>
//Include the macros
#include <FSM_MACROS.h>

int Led = 13;
int LedBoton = 12;
int boton = 2;

//Setup FSM with millis time reference
FSM_SETUP(millis)

//Create State's Functions
FSM_STATE_FUNCTION(Conf) {
  pinMode(Led, OUTPUT);
}
FSM_STATE_FUNCTION(On) {
  digitalWrite(Led, HIGH);
}
FSM_STATE_FUNCTION(Off) {
  digitalWrite(Led, LOW);
}

FSM_STATE_FUNCTION(ConfLed) {
  pinMode(LedBoton, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
}
FSM_STATE_FUNCTION(LedOn) {
  digitalWrite(LedBoton, HIGH);
}
FSM_STATE_FUNCTION(LedOff) {
  digitalWrite(LedBoton, LOW);
}

//Define States
FSM_STATE(S0, Conf, nullptr, nullptr);
FSM_STATE(S1, On, nullptr, nullptr);
FSM_STATE(S2, Off, nullptr, nullptr);
FSM_STATE(S3, ConfLed, nullptr, nullptr);
FSM_STATE(S4, LedOn, nullptr, nullptr);
FSM_STATE(S5, LedOff, nullptr, nullptr);


//Define Transition's conditions
FSM_TRANSITION_CONDITION(Delay1s) {
  return RUN_TIME > 1000;
}
FSM_TRANSITION_CONDITION(ButtonDown) {
  return !digitalRead(boton);
}
FSM_TRANSITION_CONDITION(ButtonUp) {
  return digitalRead(boton);
}

//Define Transitions
FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, Delay1s);
FSM_TRANSITION(T2, S2, S1, Delay1s);

FSM_TRANSITION(T3, S3, S4, Instant);
FSM_TRANSITION(T4, S4, S5, ButtonDown);
FSM_TRANSITION(T5, S5, S4, ButtonUp);


void setup() {
  //Setup Initial States
  FSM_INITIAL_STATE(S0);
  FSM_INITIAL_STATE(S3);
}

void loop() {
  //Run FSM
  FSM_RUN();
}
