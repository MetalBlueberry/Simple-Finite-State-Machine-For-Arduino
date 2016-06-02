#include "Transition.h"
#include "State.h"
#include "FSM.h"
#include "SimpleList/SimpleList.h"


Transition::Transition(State* from, State* to ,bool (*condition)(State ,State))
{

	_from = from;
	_to = to;

	_condition = condition;

	_Condition = nullptr;
	_Action = nullptr;

	FSM::add(this);
}

Transition::Transition(bool (*Condition)(),void (*Action)())
{
	_Condition = Condition;
	_Action = Action;
	FSM::add(this);
}

void Transition::now(State* from, State* to)
{
	from->nextState = false;
	to->nextState = true;
}

void Transition::Execute()
{
	if(_Condition != nullptr)
	{
		if(_Condition()) {
			_Action();
		}
		}else{
		if(_from->status() && _condition(*_from,*_to)){
			_from->nextState = false;
			_to->nextState = true;
		}
	}

}




bool Transition::CheckForeach(State* array[], unsigned char count)
{
	for(int i = 0;i < count ;i++){
		if(!(array[i])->status()){
			return false;
		}
	}
	return true;
}

void Transition::SetForeach(State* array[], unsigned char count)
{
	for(int i = 0;i < count ;i++){
		(array[i])->nextState = true;
	}
}

void Transition::ClearForeach(State* array[], unsigned char count)
{
	for(int i = 0;i < count ;i++){
		(array[i])->nextState = false;
	}
}
