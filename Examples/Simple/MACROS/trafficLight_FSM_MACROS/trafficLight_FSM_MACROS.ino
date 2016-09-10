#include <FSM.h>
#include <FSM_MACROS.h>;
FSM_SETUP(millis)

int RedLed = 12;
int YelowLed = 11;
int GreenLed = 13;

FSM_STATE_FUNCTION(setup_function) {
  pinMode(RedLed, OUTPUT);
  pinMode(YelowLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
}

FSM_STATE_FUNCTION(ONRed) {
  digitalWrite(RedLed, HIGH);
  digitalWrite(YelowLed, LOW);
  digitalWrite(GreenLed, LOW);
}

FSM_STATE_FUNCTION(ONYellow) {
  digitalWrite(RedLed, LOW);
  digitalWrite(YelowLed, HIGH);
  digitalWrite(GreenLed, LOW);
}

FSM_STATE_FUNCTION(ONGreen) {
  digitalWrite(RedLed, LOW);
  digitalWrite(YelowLed, LOW);
  digitalWrite(GreenLed, HIGH);
}


FSM_STATE(Setup, setup_function, nullptr, nullptr);
FSM_STATE(Red, ONRed, nullptr, nullptr);
FSM_STATE(Yellow, ONYellow, nullptr, nullptr);
FSM_STATE(Green, ONGreen, nullptr, nullptr);


FSM_TRANSITION_CONDITION(TIn5s) {
  return RUN_TIME > 5000;
}
FSM_TRANSITION_CONDITION(TIn10s) {
  return RUN_TIME > 10000;
}
FSM_TRANSITION_CONDITION(TIn3s) {
  return RUN_TIME > 3000;
}


FSM_TRANSITION(T1, Setup, Red, Instant);
FSM_TRANSITION(T2, Red, Yellow, TIn10s);
FSM_TRANSITION(T3, Yellow, Green, TIn3s);
FSM_TRANSITION(T4, Green, Red, TIn5s);

void setup() {
  FSM_INITIAL_STATE(Setup);
}

void loop() {
  FSM_RUN();
}
