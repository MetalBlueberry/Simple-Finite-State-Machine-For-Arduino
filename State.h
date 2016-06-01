/**************************************************
Autor: V�ctor P�rez Domingo
Fecha: 12/05/2016

Clase estado para la libreria FSM

*************************************************/
#define FSM_CONTROL_DE_TIEMPO

#ifndef State_h
#define  State_h
#include "arduino.h"

class State{
	friend class FSM;
	friend class Transition;

	
	public:
	unsigned int id;
	bool nextState = false;
	bool status();
	State(void (*In)(State*),void (*Run)(State*),void (*Out)(State*));
	#ifdef FSM_CONTROL_DE_TIEMPO
		/**
		* Tiempo en ms desde el inicio del estado
		*/
		unsigned long runTime();
	#endif
	private:
	static unsigned int count;
	#ifdef FSM_CONTROL_DE_TIEMPO
		unsigned long _runTime;
		void InternalIn();
	#endif
	void (*In)(State*) = nullptr;
	void (*Run)(State*) = nullptr;
	void (*Out)(State*) = nullptr;
	bool _lastState = false;
	bool _thisState = false;
	
	

	
};


#endif