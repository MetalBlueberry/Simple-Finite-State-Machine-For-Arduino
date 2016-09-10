FSM_STATE_FUNCTION(setup_function) {
  Light1.Configurar();
  Light2.Configurar();
}

FSM_STATE_FUNCTION(Road1) {
  Light1.Write(RedColor);
  Light2.Write(GreenColor);
}

FSM_STATE_FUNCTION(Road2) {
  Light1.Write(GreenColor);
  Light2.Write(RedColor);
}

FSM_STATE_FUNCTION(Road1a2) {
  Light1.Write(RedColor);
  Light2.Write(YellowColor);
}

FSM_STATE_FUNCTION(Road2a1) {
  Light1.Write(YellowColor);
  Light2.Write(RedColor);
}

FSM_STATE_FUNCTION(WaitRed) {
  Light1.Write(RedColor);
  Light2.Write(RedColor);
}

FSM_STATE(Setup, setup_function, nullptr, nullptr);
FSM_STATE(S_Road1, Road1, nullptr, nullptr);
FSM_STATE(S_Road2, Road2, nullptr, nullptr);
FSM_STATE(S_Road1a2, Road1a2, nullptr, nullptr);
FSM_STATE(S_Road2a1, Road2a1, nullptr, nullptr);
FSM_STATE(S_Wait1a2, WaitRed, nullptr, nullptr);
FSM_STATE(S_Wait2a1, WaitRed, nullptr, nullptr);


FSM_TRANSITION_CONDITION(TIn3s) {
  return RUN_TIME > 3000;
}
FSM_TRANSITION_CONDITION(TIn10s) {
  return RUN_TIME > 10000;
}
FSM_TRANSITION_CONDITION(TIn2s) {
  return RUN_TIME > 2000;
}


FSM_TRANSITION(T1, Setup, S_Road1, Instant);
FSM_TRANSITION(T2, S_Road1, S_Road1a2, TIn10s);
FSM_TRANSITION(T3, S_Road2, S_Road2a1, TIn10s);
FSM_TRANSITION(T4, S_Road2a1, S_Wait2a1, TIn3s);
FSM_TRANSITION(T5, S_Road1a2, S_Wait1a2, TIn3s);
FSM_TRANSITION(T6, S_Wait2a1, S_Road1, TIn2s);
FSM_TRANSITION(T7, S_Wait1a2, S_Road2, TIn2s);



