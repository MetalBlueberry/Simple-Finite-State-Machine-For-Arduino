/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Clase Transition para la libreria FSM

*************************************************/

#ifndef Transition_h
#define Transition_h
#include "State.h"
#include "SimpleList/SimpleList.h"

class Transition
{
	friend class FSM;
	public:
	//Transition(State* from,unsigned char fromCount, State* to,unsigned char toCount, bool (*condition)(State*,unsigned char,State*,unsigned char));
	//Transition(State* from[],unsigned char fromCount, State* to[],unsigned char toCount ,bool (*condition)(State ,State));
	Transition(State* from, State* to ,bool (*condition)(State ,State));
	Transition(bool (*Condition)(),void (*Action)());
	static void now(State* from, State* to);
	private:
	void Execute();
	State* _from;
	//unsigned char _fromCount;
	State* _to;
	//unsigned char _toCount;*/
	bool (*_Condition)();
	void (*_Action)();
	bool (*_condition)(State,State);

	bool CheckForeach(State* array[], unsigned char count);
	void SetForeach(State* array[], unsigned char count);
	void ClearForeach(State* array[], unsigned char count);
};

#endif
