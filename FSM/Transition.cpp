#include "Transition.h"
#include "State.h"
#include "FSM.h"


/*Transition::Transition(State* from, State* to, bool (*condition)())
{
	_from = new State*[1];
	_from[0] = from;
	_fromCount = 1;
	_to = new State*[1];
	_to[0] = to;
	_toCount = 1;
	_condition = condition;

	
	D("Estado nuevo ");
	D(_from[0]->id);
	D(":");
	D(_from[0]->_lastState);
	D(" ");
	D(_from[0]->_thisState);
	D(" ");
	Dln(_from[0]->nextState);
	FSM::add(this);
}*/
/*
Transition::Transition(State* from, State* to, bool (*condition)(State*,State*))
{
	_from = new State*[1];
	_from[0] = from;
	_fromCount = 1;
	_to = new State*[1];
	_to[0] = to;
	_toCount = 1;
	_condition = condition;

	
	D("Estado nuevo ");
	D(_from[0]->id);
	D(":");
	D(_from[0]->_lastState);
	D(" ");
	D(_from[0]->_thisState);
	D(" ");
	Dln(_from[0]->nextState);
	FSM::add(this);
}
*/
 Transition::Transition(State* from,unsigned char fromCount, State* to,unsigned char toCount, bool (*condition)(State*,unsigned char,State*,unsigned char))
{
	_from = new State*[fromCount];
	_from[0] = from;
	_fromCount = fromCount;
	_to = new State*[toCount];
	_to[0] = to;
	_toCount = toCount;
	_condition = condition;

	/*
	D("Estado nuevo ");
	D(_from[0]->id);
	D(":");
	D(_from[0]->_lastState);
	D(" ");
	D(_from[0]->_thisState);
	D(" ");
	Dln(_from[0]->nextState);*/
	FSM::add(this);
}

/*
Transition::Transition(State** from,int fromCount, State** to, int toCount, bool (*condition)())
{
_from = from;
//_fromCount = fromCount;
_to =  to;
//_toCount = toCount;
_condition = condition;
FSM::add(this);
}*/

void Transition::now(State* from, State* to)
{

	from->nextState = false;
	to->nextState = true;
	
}

void Transition::Execute()
{
	/*	D("Transition ");
	D(_from->id);
	D(":");
	D(_from->_lastState);
	D(" ");
	D(_from->_thisState);
	D(" ");
	Dln(_from->nextState);*/
	/*if ((_from[0])->status() && _condition()){
	(_from[0])->nextState = false;
	(_to[0])->nextState = true;
	
	}*/
	if(CheckForeach(_from,_fromCount) && _condition(_from[0],_fromCount,_to[0],_toCount)){
		ClearForeach(_from,_fromCount);
		SetForeach(_to,_toCount);
	}
}


bool Transition::CheckForeach(State** array, unsigned char count)
{
	for(int i = 0;i < count ;i++){
		if(!(array[i])->status()){
			return false;
		}
	}
	return true;
}

void Transition::SetForeach(State** array, unsigned char count)
{
	for(int i = 0;i < count ;i++){
		(array[i])->nextState = true;
	}
}

void Transition::ClearForeach(State** array, unsigned char count)
{
	for(int i = 0;i < count ;i++){
		(array[i])->nextState = false;
	}
}
