/**************************************************
  Autor: Víctor Pérez Domingo
  Fecha: 12/05/2016

  Led 13 blinks at 1 time per second
  Led 12 Blinks at 10 times per second
  All independently
  
This example shows how to use external data to customise functions depending on the state.
Este ejemplo demuestra como utilizar datos externos para personalizar las funciones dependiendo del estado.

*************************************************/

//Include the library
#include <FSM.h>
//Include the macros
#include <FSM_MACROS.h>

//Setup FSM with millis time reference
FSM_SETUP(millis)

class Datos{
public: 
  int pin;
  int delayOn;
  int delayOff;
  Datos(int pin, int delayOn, int delayOff){
    this->pin = pin;
    this->delayOn = delayOn; 
    this->delayOff = delayOff;
  }
};
Datos datos1(13,1000,1000);
Datos datos2(12,500,1000);

//Create State's Functions
FSM_STATE_FUNCTION(Conf) {
  //dataType * data = static_cast< dataType *> (from->genericData)
  CUSTOM_DATA(Datos);
  pinMode(data->pin, OUTPUT);
}
FSM_STATE_FUNCTION(On) {
  CUSTOM_DATA(Datos);
  digitalWrite(data->pin, HIGH);
}
FSM_STATE_FUNCTION(Off) {
  CUSTOM_DATA(Datos);
  digitalWrite(data->pin, LOW);
}


//Define States
FSM_STATE(S0, Conf, nullptr, nullptr,&datos1);
FSM_STATE(S1, On, nullptr, nullptr,&datos1);
FSM_STATE(S2, Off, nullptr, nullptr,&datos1);

FSM_STATE(S3, Conf, nullptr, nullptr,&datos2);
FSM_STATE(S4, On, nullptr, nullptr,&datos2);
FSM_STATE(S5, Off, nullptr, nullptr,&datos2);


//Define Transition's conditions
FSM_TRANSITION_CONDITION(DelayOn) {
  CUSTOM_DATA(Datos);
  return RUN_TIME > data->delayOn;
}
FSM_TRANSITION_CONDITION(DelayOff) {
  CUSTOM_DATA(Datos);
  return RUN_TIME > data->delayOff;
}

//Define Transitions
FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, DelayOn);
FSM_TRANSITION(T2, S2, S1, DelayOff);

FSM_TRANSITION(T3, S3, S4, Instant);
FSM_TRANSITION(T4, S4, S5, DelayOn);
FSM_TRANSITION(T5, S5, S4, DelayOff);


void setup() {
  FSM_INITIAL_STATE(S0);
  FSM_INITIAL_STATE(S3);
}

void loop() {
  FSM_RUN();
}

