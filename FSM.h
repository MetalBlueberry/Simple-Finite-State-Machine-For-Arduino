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



#ifndef FSM_h

#define FSM_MACROS
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
#define UNPACK(...) __VA_ARGS__

#define FSM_TRANSITION_CONDITION(funcion) \
bool funcion (State from, State to)
#define FSM_TRANSITION_CONDITION_MULTI(funcion)\
bool funcion ()


#define NUMARGS(...)  (sizeof((State*[]){__VA_ARGS__})/sizeof(State*))
#define FSM_PREVIOUS_STATES(...)  (FSM::AndAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_FROM_STATES(...)  (FSM::ClearAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_TO_STATES(...)  (FSM::SetAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))

#define FSM_TRANSITION_MULTI_CONDITIONS(nombre, condition , ...)\
bool nombre ## _conditions(){\
	return FSM_PREVIOUS_STATES(__VA_ARGS__) && condition ();\
}\
void nombre ## _actions(){\
	FSM_FROM_STATES(__VA_ARGS__)
	
	#define FSM_TRANSITION_MULTI_ACTIONS(nombre,...)\
	FSM_TO_STATES(__VA_ARGS__);\
}\
Transition nombre( nombre ## _conditions,nombre ## _actions)

#define FSM_TRANSITION(nombre, from, to, condition )\
Transition nombre(&from,&to,condition)

#define FSM_TRANSITION(nombre, from, to, condition )\
bool nombre ## _conditions(){\
	return from.status() && condition (from, to);\
}\
void nombre ## _actions(){\
	from.nextState = false;\
	to.nextState = true;\
}\
Transition nombre( nombre ## _conditions,nombre ## _actions)

#define INSTANT \
FSM_TRANSITION_CONDITION(Instant){return true;}\
FSM_TRANSITION_CONDITION_MULTI(Instant){return true;}

#endif


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
	static bool AndAll(int numargs, ...);
	static void ClearAll(int numargs, ...);
	static void SetAll(int numargs, ...);
	//static void reserve(int s,int t);
	static void Run();
	
	
};


#endif
