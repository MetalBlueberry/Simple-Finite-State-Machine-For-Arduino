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
//Auxiliary macros, you don't need to use this
#define UNPACK(...) __VA_ARGS__
#define NUMARGS(...)  (sizeof((State*[]){__VA_ARGS__})/sizeof(State*))
#define FIRST(...) FIRST_HELPER(__VA_ARGS__, throwaway)
#define FIRST_HELPER(first, ...) first
#define FSM_PREVIOUS_STATES(...)  (FSM::AndAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_FROM_STATES(...)  (FSM::ClearAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_TO_STATES(...)  (FSM::SetAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_TRANSITION_MULTI_CONDITIONS(name, condition , from, to , ...)\
bool name ## _conditions(){\
	return FSM_PREVIOUS_STATES(__VA_ARGS__) && condition (from,to);\
}\
void name ## _actions(){\
	FSM_FROM_STATES(__VA_ARGS__)
	
#define FSM_TRANSITION_MULTI_ACTIONS(name,...)\
	FSM_TO_STATES(__VA_ARGS__);\
}\
Transition name( name ## _conditions,name ## _actions)

//Macros
//Execute the FSM
#define FSM_RUN FSM::Run()
//Create a new State Function for use it as In Run or Out
#define FSM_STATE_FUNCTION(name) void name (State* s)
//Create a new State
#define FSM_STATE(name, In,Run,Out) \
State name(In,Run,Out)
//Set initial states
#define FSM_INITIAL_STATE(name) name.nextState = true
//Create a transition conditions function 
#define FSM_TRANSITION_CONDITION(function) \
bool function (State* from, State* to)


//create a transition from multiple states to multiple states
#define FSM_TRANSITION_MULTI(name, condition, from, to)\
FSM_TRANSITION_MULTI_CONDITIONS(name, condition, FIRST(UNPACK from) , FIRST(UNPACK to), UNPACK from);\
FSM_TRANSITION_MULTI_ACTIONS(name, UNPACK to);

//create a simple transition from a state to an other
#define FSM_TRANSITION(name, from, to, condition )\
bool name ## _conditions(){\
	return from.status() && condition (&from, &to);\
}\
void name ## _actions(){\
	from.nextState = false;\
	to.nextState = true;\
}\
Transition name( name ## _conditions,name ## _actions)

//Utilities
//creates an instant transition called Instant
#define INSTANT \
FSM_TRANSITION_CONDITION(Instant){return true;}\	




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
	static void Run();
	
	
};


#endif
