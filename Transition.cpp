#include "Transition.h"
#include "State.h"
#include "FSM.h"



 Transition::Transition(State* from,unsigned char fromCount, State* to,unsigned char toCount, bool (*condition)(State*,unsigned char,State*,unsigned char))
{
	_from = new State*[fromCount];
	_from[0] = from;
	_fromCount = fromCount;
	_to = new State*[toCount];
	_to[0] = to;
	_toCount = toCount;
	_condition = condition;

	FSM::add(this);
}


void Transition::now(State* from, State* to)
{

	from->nextState = false;
	to->nextState = true;
	
}

void Transition::Execute()
{

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
