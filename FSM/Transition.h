/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Clase Transition para la libreria FSM

*************************************************/

#ifndef Transition_h
#define Transition_h
#include "State.h"
class Transition
{
	friend class FSM;
	public:
	Transition(State* from,unsigned char fromCount, State* to,unsigned char toCount, bool (*condition)(State*,unsigned char,State*,unsigned char));
	static void now(State* from, State* to);
	private:
	void Execute();

	State** _from;
	//State** _fromArray;
	unsigned char _fromCount;
	State** _to;
	//State** _toArray;
	unsigned char _toCount;
	bool (*_condition)(State*,unsigned char,State*,unsigned char);
	bool CheckForeach(State** array, unsigned char count);
	void SetForeach(State** array, unsigned char count);
	void ClearForeach(State** array, unsigned char count);
};

#endif
