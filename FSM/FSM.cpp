
#include "FSM.h"
//#include "QueueList/QueueList.h"
#include "Transition.h"
#include "SimpleList/SimpleList.h"

SimpleList<Transition*> FSM::Transitions;
SimpleList<State*> FSM::States;

void FSM::add(State* s)
{
	States.push_back(s);
}
void FSM::add(Transition* t){
	
	Transitions.push_back(t);
}

/*void FSM::reserve(int s,int t)
{
	States.reserve(s);
	Transitions.reserve(t);
}*/

void FSM::Run()
{

	//inline iterator begin() { return _internalArray; }
	//inline iterator end() { return _internalArray + _endPosition; }
	
	State** s = States.begin();
	for (unsigned int i = 0; i < States.size();i++)
	{
		s[i]->_lastState = s[i]->_thisState;
		s[i]->_thisState = s[i]->nextState;
		//D("Estado ");
		/*D(s[i]->id);
		D(":");
		D(s[i]->_lastState);
		D(" ");
		D(s[i]->_thisState);
		D(" ");
		Dln(s[i]->nextState);*/
		if(s[i]->_lastState && !s[i]->_thisState){
			if(s[i]->Out != nullptr){
				s[i]->Out(s[i]);
			}
		}
	}
	for (unsigned int i = 0; i < States.size();i++)
	{
		if(!s[i]->_lastState && s[i]->_thisState){
			s[i]->InternalIn();
			if(s[i]->In != nullptr){
				s[i]->In(s[i]);
			}
		}
	}
	for (unsigned int i = 0; i < States.size();i++)
	{
		if(s[i]->_lastState && s[i]->_thisState){
			if(s[i]->Run != nullptr){
				s[i]->Run(s[i]);
			}
		}
	}
	
	Transition** t = Transitions.begin();
	for (unsigned int i = 0; i < Transitions.size();i++)
	{
		t[i]->Execute();
	}




	
}