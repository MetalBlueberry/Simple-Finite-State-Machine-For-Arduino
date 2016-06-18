/* Led 13 blinks at 1 time per second
    Led 12 Blinks at 10 times per second
    Sync metod wait until bot tasks end to continue
*/
//Include the library
#include "FSM.h"
//Setup FSM with millis time reference
FSM_SETUP(millis)

//Create State's Functions
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
}
FSM_STATE_FUNCTION(LedOn) {
  digitalWrite(12, HIGH);
}
FSM_STATE_FUNCTION(LedOff) {
  digitalWrite(12, LOW);
}


//Define States
FSM_STATE(S0, Conf, nullptr, nullptr);
FSM_STATE(S1, On, nullptr, nullptr);
FSM_STATE(S2, Off, nullptr, nullptr);
FSM_STATE(S2_wait, nullptr, nullptr, nullptr);
FSM_STATE(S3, ConfLed, nullptr, nullptr);
FSM_STATE(S4, LedOn, nullptr, nullptr);
FSM_STATE(S5, LedOff, nullptr, nullptr);
FSM_STATE(S5_wait, nullptr, nullptr, nullptr);

//Define Transition's conditions
FSM_TRANSITION_CONDITION(Delay1s) {
  return RUN_TIME > 1000;
}
FSM_TRANSITION_CONDITION(Delay100ms) {
  return RUN_TIME > 100;
}

//Define Transitions
FSM_TRANSITION_MULTI(TSync1, (&S2_wait, &S5_wait), (&S1, &S4), Instant);

FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, Delay1s);
FSM_TRANSITION(T2, S2, S2_wait, Delay1s);

FSM_TRANSITION(T3, S3, S4, Instant);
FSM_TRANSITION(T4, S4, S5, Delay100ms);
FSM_TRANSITION(T5, S5, S5_wait, Delay100ms);


void setup() {
  //Setup Initial States
  FSM_INITIAL_STATE(S0);
  FSM_INITIAL_STATE(S3);
}

void loop() {
  //Run FSM
  FSM_RUN;
}


