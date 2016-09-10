/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Clase Transition para la libreria FSM

*************************************************/

#include <States/Transition.h>
#include <States/State.h>
#include <FSM.h>
#include <SimpleList/SimpleList.h>


Transition::Transition(bool (*Condition)(),void (*Action)())
{
    _Condition = Condition;
    _Action = Action;
    FSM::Instance.add(this);
}

void Transition::now(State* from, State* to)
{
    from->nextState = false;
    to->nextState = true;
}

void Transition::Execute()
{
    if(Condition()) {
        _Action();
    }
}

bool Transition::Condition()
{
    if(_Condition != nullptr)
    {
        return(_Condition());
    }
}
