#include <States/State.h>
#include <FSM.h>


State::State(void(*In)(State*), void(*Run)(State*), void(*Out)(State*))
{
    this->In = In;
    this->Run = Run;
    this->Out = Out;
    this->genericData = nullptr;
    FSM::Instance.add(this);
}

State::State(void(*In)(State*), void(*Run)(State*), void(*Out)(State*), void *genericData)
{
    this->In = In;
    this->Run = Run;
    this->Out = Out;
    this->genericData = genericData;
    FSM::Instance.add(this);
}

#ifdef FSM_CONTROL_DE_TIEMPO
unsigned long State::runTime()
{
    if (FSM::Instance.RunTime == nullptr) {
        return 0;
    }
    return FSM::Instance.RunTime() - _runTime;
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



