/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Esta libreria permite programar utilizando la tecnica de FSM de una manera facil y sencilla

This library allows you to design FSM nets in a easy way.

*************************************************/
#include <FSM.h>
#include <States/Transition.h>
#include <SimpleList/SimpleList.h>

//FSM FSM::Instance;

FSM::FSM() {
	SimpleList<Transition*> Transitions;
	SimpleList<State*> States;
}
FSM::FSM(unsigned long(*RunTime)())
{
	SimpleList<Transition*> Transitions;
	SimpleList<State*> States;
	this->RunTime = RunTime;
}
void FSM::add(State* s)
{
	States.push_back(s);
}
void FSM::add(Transition* t){
	
	Transitions.push_back(t);
}

bool FSM::AndAll(int numargs, ...)
{
	bool total = true;
	
	va_list ap;
	va_start(ap, numargs);
	while (numargs--)
	total = total && va_arg(ap, State*)->status();
	va_end(ap);

	return total;
}

bool FSM::AnyFrom(int numargs, ...)
{
	bool total = false;

	va_list ap;
	va_start(ap, numargs);
	while (numargs--) {
		total = total || va_arg(ap, State*)->status();
		if(total) break;
	}
	va_end(ap);

	return total;
}

void FSM::ClearAll(int numargs, ...)
{
	va_list ap;
	va_start(ap, numargs);
	while (numargs--)
		va_arg(ap, State*)->nextState = false;
	va_end(ap);
}

void FSM::SetAll(int numargs, ...)
{
	va_list ap;
	va_start(ap, numargs);
	while (numargs--)
	va_arg(ap, State*)->nextState = true;
	va_end(ap);
}



void FSM::Run()
{
	State** s = States.begin();
	for (unsigned int i = 0; i < States.size();i++)
	{
		s[i]->_lastState = s[i]->_thisState;
		s[i]->_thisState = s[i]->nextState;

		if(s[i]->_lastState && !s[i]->_thisState){
			if(s[i]->Out != nullptr){
				s[i]->Out(s[i]);
			}
		}
	}
	for (unsigned int i = 0; i < States.size();i++)
	{
		if(!s[i]->_lastState && s[i]->_thisState){
			#ifdef FSM_CONTROL_DE_TIEMPO
			s[i]->InternalIn();
			#endif
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
