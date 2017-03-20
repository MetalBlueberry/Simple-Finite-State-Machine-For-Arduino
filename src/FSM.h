/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Esta libreria permite programar utilizando la tecnica de FSM de una manera facil y sencilla

This library allows you to design FSM nets in an easy way.

*************************************************/

/**************************************************
Instructions:
TODO

*************************************************/


#ifndef FSM_h
#define FSM_h



#include <States/State.h>
#include <States/Transition.h>
#include <SimpleList/SimpleList.h>
#include <stdarg.h>

class FSM {

    friend class Transition;
    friend class State;
private:
    //Listas de transiciones y estados creadas de manera dinamica
    SimpleList<Transition*> Transitions;
    SimpleList<State*> States;

    void add(State* s);
    void add(Transition* s);

    //Constructor sin referencia de tiempo, No es posible utilizar la función RunTime si se utiliza este constructor
    FSM();
    FSM(unsigned long(*RunTime)());

public:
    //Unica instancia de la máquina
    static FSM Instance;

    unsigned long(*RunTime)() = nullptr;
    //Función vacia para evitar errores si no se declara RunTime
    static long RunTimeNull();

    //Ejecuta la máquina
    void Run();

    //Funciones para manipular y comprobar el estado de los estados de la máquina
    static bool AndAll(int numargs, ...);
    static bool AnyFrom(int numargs, ...);
    static void ClearAll(int numargs, ...);
    static void SetAll(int numargs, ...);

};

#endif
