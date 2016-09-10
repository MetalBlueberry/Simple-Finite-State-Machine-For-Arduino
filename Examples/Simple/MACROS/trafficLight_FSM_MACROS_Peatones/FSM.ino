FSM_STATE_FUNCTION(setup_function) {
  Luz1.Configurar();
  Luz2.Configurar();

  pinMode(LuzPeatonal, OUTPUT);
  pinMode(LuzBoton, OUTPUT);
  pinMode(Sonido, OUTPUT);
  pinMode(BotonPeatonal, INPUT_PULLUP);
}

FSM_STATE_FUNCTION(Paso1) {
  Luz1.Write(ColorRojo);
  Luz2.Write(ColorVerde);
}

FSM_STATE_FUNCTION(Paso2) {
  Luz1.Write(ColorVerde);
  Luz2.Write(ColorRojo);
  digitalWrite(LuzPeatonal, LOW);
}

FSM_STATE_FUNCTION(Paso1a2) {
  Luz1.Write(ColorRojo);
  Luz2.Write(ColorAmarillo);
  digitalWrite(LuzPeatonal, LOW);
}

FSM_STATE_FUNCTION(Paso2a1) {
  Luz1.Write(ColorAmarillo);
  Luz2.Write(ColorRojo);
  digitalWrite(LuzPeatonal, LOW);
}

FSM_STATE_FUNCTION(EsperaEnRojo) {
  Luz1.Write(ColorRojo);
  Luz2.Write(ColorRojo);
  digitalWrite(LuzPeatonal, LOW);
}

FSM_STATE_FUNCTION(DejarPasarPeatones) {
  Luz1.Write(ColorRojo);
  Luz2.Write(ColorRojo);
  digitalWrite(LuzPeatonal, HIGH);
}

FSM_STATE_FUNCTION(HacerRuidoNormal) {
  if ((RUN_TIME / 200) % 2 == 0) {
    digitalWrite(Sonido, HIGH);
  } else {
    digitalWrite(Sonido, LOW);
  }
}
FSM_STATE_FUNCTION(HacerAviso) {
  if ((RUN_TIME / 200) % 4 == 0) {
    digitalWrite(Sonido, HIGH);
  } else {
    digitalWrite(Sonido, LOW);
  }
  if ((RUN_TIME / 200) % 2 == 0) {
    digitalWrite(LuzPeatonal, HIGH);
  } else {
    digitalWrite(LuzPeatonal, LOW);
  }

}
FSM_STATE_FUNCTION(PararRuido) {
  digitalWrite(Sonido, LOW);
}

FSM_STATE_FUNCTION(EncenderLuzBoton) {
  digitalWrite(LuzBoton, HIGH);
}
FSM_STATE_FUNCTION(ApagarLuzBoton) {
  digitalWrite(LuzBoton, LOW);
}

FSM_STATE(Setup, setup_function, nullptr, nullptr);
FSM_STATE(S_Paso1, Paso1, nullptr, nullptr);
FSM_STATE(S_Paso2, Paso2, nullptr, nullptr);
FSM_STATE(S_Paso1a2, Paso1a2, nullptr, nullptr);
FSM_STATE(S_Paso2a1, Paso2a1, nullptr, nullptr);
FSM_STATE(S_Espera1a2, EsperaEnRojo, nullptr, nullptr);
FSM_STATE(S_Espera2a1, EsperaEnRojo, nullptr, nullptr);

FSM_STATE(S_DejarPasarPeatones, DejarPasarPeatones, HacerRuidoNormal, nullptr);
FSM_STATE(S_AvisarPeatones, EsperaEnRojo, HacerAviso, PararRuido);
FSM_STATE(S_EsperarPeatones, EsperaEnRojo, nullptr, nullptr);

FSM_STATE(S_NoHayPeatones, ApagarLuzBoton, nullptr, nullptr);
FSM_STATE(S_HayPeatones, EncenderLuzBoton, nullptr, nullptr);


FSM_TRANSITION_CONDITION(TIn3s) {
  return RUN_TIME > 3000;
}
FSM_TRANSITION_CONDITION(TIn10s) {
  return RUN_TIME > 10000;
}
FSM_TRANSITION_CONDITION(TIn2s) {
  return RUN_TIME > 2000;
}
FSM_TRANSITION_CONDITION(TIn5s) {
  return RUN_TIME > 5000;
}

FSM_TRANSITION_CONDITION(PulsandoBoton) {
  return !digitalRead(BotonPeatonal);
}

FSM_TRANSITION_CONDITION(PeatonesEsperando) {
  return RUN_TIME > 1500 && S_HayPeatones.status();
}


FSM_TRANSITION_MULTI(T1, (&Setup), (&S_Paso1, &S_NoHayPeatones), Instant, false);

FSM_TRANSITION(T2, S_Paso1, S_Paso1a2, TIn10s);
FSM_TRANSITION(T3, S_Paso2, S_Paso2a1, TIn10s);
FSM_TRANSITION(T4, S_Paso2a1, S_Espera2a1, TIn3s);
FSM_TRANSITION(T5, S_Paso1a2, S_Espera1a2, TIn3s);
FSM_TRANSITION(T6, S_Espera2a1, S_Paso1, TIn2s);
FSM_TRANSITION(T7, S_Espera1a2, S_Paso2, TIn2s);

FSM_TRANSITION(T8, S_Espera2a1, S_DejarPasarPeatones, PeatonesEsperando);
FSM_TRANSITION(T9, S_Espera1a2, S_DejarPasarPeatones, PeatonesEsperando);

FSM_TRANSITION(T10, S_DejarPasarPeatones, S_AvisarPeatones, TIn5s);
FSM_TRANSITION(T11, S_AvisarPeatones, S_EsperarPeatones, TIn2s);

FSM_TRANSITION_MULTI(T12, (&S_EsperarPeatones, &S_HayPeatones), (&S_Paso1 , &S_NoHayPeatones) , TIn2s, false);

FSM_TRANSITION(TBoton, S_NoHayPeatones, S_HayPeatones, PulsandoBoton);


