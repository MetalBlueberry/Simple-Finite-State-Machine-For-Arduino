/**************************************************
  Autor: Víctor Pérez Domingo
  Fecha: 12/05/2016

  Pin 13 blinks, 
  Not recomended if you don't know what are you doing
*************************************************/

//Include the library
#include <FSM.h>
//Include the macros
//#include <FSM_MACROS.h>
//Setup FSM with millis time reference
//FSM_SETUP(millis)
FSM FSM::Instance(millis);
bool Instant (State* from, State* to) {
  return true;
}

//Create State's Functions
//FSM_STATE_FUNCTION(Conf) {
void Conf (State* from) {
  pinMode(13, OUTPUT);
}
//FSM_STATE_FUNCTION(On) {
void On (State* from) {
  digitalWrite(13, HIGH);
}
//FSM_STATE_FUNCTION(Off) {
void Off (State* from) {
  digitalWrite(13, LOW);
}

//Define States
//FSM_STATE(S0, Conf, nullptr, nullptr);
State S0(Conf, nullptr, nullptr );
//FSM_STATE(S1, On, nullptr, nullptr);
State S1(On, nullptr, nullptr );
//FSM_STATE(S2, Off, nullptr, nullptr);
State S2(Off, nullptr, nullptr );

//Define Transition's conditions
//FSM_TRANSITION_CONDITION(Delay1s) {
bool Delay1s (State* from, State* to) {
  return from->runTime() > 1000;
}

//Define Transitions
//FSM_TRANSITION(T0, S0, S1, Instant);
bool T0_conditions() {
  return S0.status() && Instant(&S0, &S1);
}
void T0_actions() {
  S0.nextState = false;
  S1.nextState = true;
}
Transition T0( T0_conditions, T0_actions);

//FSM_TRANSITION(T1, S1, S2, Delay1s);
bool T1_conditions() {
  return S1.status() && Delay1s(&S1, &S2);
}
void T1_actions() {
  S1.nextState = false;
  S2.nextState = true;
}
Transition T1( &T1_conditions, &T1_actions);

//FSM_TRANSITION(T2, S2, S1, Delay1s);
bool T2_conditions() {
  return S2.status() && Delay1s(&S2, &S1);
}
void T2_actions() {
  S2.nextState = false;
  S1.nextState = true;
}
Transition T2( T2_conditions, T2_actions);


void setup() {
  //Setup Initial States
  //FSM_INITIAL_STATE(S0);
  S0.nextState = true;
}

void loop() {
  //Run FSM
  //FSM_RUN();
  FSM::Instance.Run();

}
