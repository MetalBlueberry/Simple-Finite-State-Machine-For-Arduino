/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Clase estado para la libreria FSM

*************************************************/

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
	
	/**
	* Tiempo en ms desde el inicio del estado
	*/
	unsigned long runTime();
	
	private:
	static unsigned int count;
	unsigned long _runTime;
	void (*In)(State*) = nullptr;
	void (*Run)(State*) = nullptr;
	void (*Out)(State*) = nullptr;
	bool _lastState = false;
	bool _thisState = false;
	void InternalIn();

	
};


#endif