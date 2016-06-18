/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Clase Transition para la libreria FSM

*************************************************/

#ifndef Transition_h
#define Transition_h
#include <States/State.h>
#include <SimpleList/SimpleList.h>

class Transition
{
	friend class FSM;
	public:
	Transition(bool (*Condition)(),void (*Action)());
	static void now(State* from, State* to);
	private:
	void Execute();
	bool (*_Condition)();
	void (*_Action)();

};

#endif
