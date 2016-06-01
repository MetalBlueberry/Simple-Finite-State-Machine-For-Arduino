

#include "State.h"
#include "FSM.h"
//#include "SimpleList/SimpleList.h"

#ifdef FSM_CONTROL_DE_TIEMPO
#include "arduino.h"
#endif

unsigned int State::count = 0;

State::State(void (*In)(State*),void (*Run)(State*),void (*Out)(State*))
{
	this->In = In;
	this->Run = Run;
	this->Out = Out;
	FSM::add(this);
	id = count;
	count++;
}

#ifdef FSM_CONTROL_DE_TIEMPO
unsigned long State::runTime()
{
	return millis()-_runTime;
}


void State::InternalIn()
{
	_runTime = millis();
}
#endif
bool State::status()
{
	return _thisState && _lastState;
}



