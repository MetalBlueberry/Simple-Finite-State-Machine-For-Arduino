/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Esta libreria permite programar utilizando la tecnica de FSM de una manera facil y sencilla

This library allows you to design FSM nets in a easy way.

*************************************************/

/**************************************************
Instructions:
TODO

*************************************************/


#ifndef FSM_h
#define  FSM_h



#include <States/State.h>
#include <States/Transition.h>
#include <SimpleList/SimpleList.h>


class FSM {

    friend class Transition;
    friend class State;
private:

    SimpleList<Transition*> Transitions;
    SimpleList<State*> States;
    void add(State* s);
    void add(Transition* s);
    FSM();
    FSM(unsigned long(*RunTime)());

public:
    static FSM Instance;

    unsigned long(*RunTime)() = nullptr;

    void Run();

    static bool AndAll(int numargs, ...);
    static bool AnyFrom(int numargs, ...);
    static void ClearAll(int numargs, ...);
    static void SetAll(int numargs, ...);

};

#endif
