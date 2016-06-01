/**************************************************
Autor: Víctor Pérez Domingo
Fecha: 12/05/2016

Esta libreria permite programar utilizando la tecnica de FSM de una manera facil y sencilla

*************************************************/

/**************************************************
Instrucciones:
Para crear un estado hay que definir primero las funciones de entrada, ejecucion y salida con el tipo void funcion(State* s);
En el caso de no necesitar una funcion se puede definir como nullptr.
Para crear transicciones se puede utilizar 2 formas:
-> El metodo estatico Transition::now(from,to); para generar una transicion en el siguiente ciclo
-> Declarar una transiccion permanente con Transition(State* from,unsigned char fromCount, State* to,unsigned char toCount, bool (*condition)(State*,unsigned char,State*,unsigned char));

Entes de empezar a funcionar se han de activar manualmente algunas fases utilizando la variable de la clase estado "nextState" marcandola como true

Para empezar a ejecutar la maquina hay que llamar al metodo estatico FSM::Run():

*************************************************/
#define FSM_MACROS


#ifndef FSM_h
#define  FSM_h


//funciones de debug
#ifdef DEBUG
#define D(s) (Serial.print(s))
#define Dln(s) (Serial.println(s))
#define DFloat(s,n) (Serial.println(s,n))
#define StartDebug(s) Serial.begin(s);delay(500); Serial.println("debug mode")
#else
#define D(s)
#define Dln(s)
#define DFloat(s,n)
#define StartDebug(s)
#endif

//Definir FSM_MACROS si se quieren utilizar los macros para simplificar la programación
#ifdef FSM_MACROS
#define FSM_RUN FSM::Run();
#define FSM_STATE_FUNCTION(nombre) void nombre (State* s)
#define FSM_STATE(nombre, In,Run,Out) \
State nombre(In,Run,Out)
#define FSM_INITIAL_STATE(nombre) nombre.nextState = true
#define FSM_TRANSITION_CONDITION_MULTI(nombre) bool nombre(State* from,unsigned char from_length,State* to,unsigned char to_length)
#define FSM_TRANSITION_CONDITION(funcion) \
bool funcion ## _aux(State from, State to);\
bool funcion(State* from,unsigned char from_length,State* to,unsigned char to_length){\
	funcion ## _aux(from[0],to[0]);\
}\
bool funcion ## _aux(State from, State to)
#define FSM_TRANSITION_MULTI(nombre,from,from_length,to,to_length,condition)\
Transition nombre(&from,from_length,&to,to_length,condition)
#define FSM_TRANSITION(nombre, from, to, condition)\
Transition nombre(&from,1,&to,1,condition)
#define FSM_TRANSITION_NOW(from, to)\
Transition::now(&from,&to)
#endif


//#include "QueueList/QueueList.h"
#include "State.h"
#include "Transition.h"
#include "SimpleList/SimpleList.h"



class FSM  {

	friend class Transition;
	friend class State;
	private:
	static SimpleList<Transition*> Transitions;
	static SimpleList<State*> States;
	static void add(State* s);
	static void add(Transition* s);
	public:
	//static void reserve(int s,int t);
	static void Run();
	
	
};


#endif
