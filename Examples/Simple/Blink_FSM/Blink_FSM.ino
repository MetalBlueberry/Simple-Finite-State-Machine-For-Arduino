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

//Define States
FSM_STATE(S0, Conf, nullptr, nullptr);
FSM_STATE(S1, On, nullptr, nullptr);
FSM_STATE(S2, Off, nullptr, nullptr);

//Define Transition's conditions
FSM_TRANSITION_CONDITION(Delay1s) {
  return RUN_TIME > 1000;
}

//Define Transitions
FSM_TRANSITION(T0, S0, S1, Instant);
FSM_TRANSITION(T1, S1, S2, Delay1s);
FSM_TRANSITION(T2, S2, S1, Delay1s);


void setup() {
  //Setup Initial States
  FSM_INITIAL_STATE(S0);
}

void loop() {
  //Run FSM
  FSM_RUN;

}
