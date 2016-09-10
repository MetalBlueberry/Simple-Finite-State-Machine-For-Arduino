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


//Auxiliary macros, you don't need to use this
#ifndef FSM_MACROS
#define  FSM_MACROS


//Auxiliary macros, you don't need to use this
#define UNPACK(...) __VA_ARGS__
#define NUMARGS(...)  (sizeof((State*[]){__VA_ARGS__})/sizeof(State*))
#define FIRST(...) FIRST_HELPER(__VA_ARGS__, throwaway)
#define FIRST_HELPER(first, ...) first
#define FSM_ANY_PREVIOUS_STATES(...)  (FSM::AnyFrom(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_PREVIOUS_STATES(...)  (FSM::AndAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_FROM_STATES(...)  (FSM::ClearAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_TO_STATES(...)  (FSM::SetAll(NUMARGS(__VA_ARGS__), __VA_ARGS__))
#define FSM_TRANSITION_MULTI_CONDITIONS(name, condition , from, to , any, ...)\
bool name ## _conditions(){\
if(any){\
        return FSM_ANY_PREVIOUS_STATES(__VA_ARGS__) && condition(from, to); \
}else {\
        return FSM_PREVIOUS_STATES(__VA_ARGS__) && condition(from, to); \
}\
}\
void name ## _actions(){\
        FSM_FROM_STATES(__VA_ARGS__)

#define FSM_TRANSITION_MULTI_ACTIONS(name,...)\
        FSM_TO_STATES(__VA_ARGS__);\
}\
Transition name( name ## _conditions,name ## _actions)

//Macros
//Execute the FSM
#define FSM_RUN FSM::Instance.Run
//Create a new State Function for use it as In Run or Out
#define FSM_STATE_FUNCTION(name) void name (State* from)
//Create a new State
#define FSM_STATE(name, In,Run,Out , ...) \
State name(In,Run,Out ,  ##__VA_ARGS__ )
//Set initial states
#define FSM_INITIAL_STATE(name) name.nextState = true
//Create a transition conditions function
#define FSM_TRANSITION_CONDITION(function) \
bool function (State* from, State* to)

#define RUN_TIME from->runTime()

//create a transition from multiple states to multiple states
#define FSM_TRANSITION_MULTI(name, from, to, condition, any)\
FSM_TRANSITION_MULTI_CONDITIONS(name, condition, FIRST(UNPACK from) , FIRST(UNPACK to), any ,UNPACK from);\
FSM_TRANSITION_MULTI_ACTIONS(name, UNPACK to);

//create a simple transition from a state to an other
#define FSM_TRANSITION(name, from, to, condition )\
bool name ## _conditions(){\
        return from.status() && condition (&from, &to);\
}\
void name ## _actions(){\
        FSM_RESET(from);\
        FSM_SET(to);\
}\
Transition name( name ## _conditions,name ## _actions)

//Utilities

#define INSTANT \
FSM_TRANSITION_CONDITION(Instant){return true;}\

#define GET_MACRO(_0,_1,NAME,...) NAME(_1)
#define FSM_SETUP(...) GET_MACRO(_0, ##__VA_ARGS__,SETUP_FSM_1,SETUP_FSM_0)

#define SETUP_FSM_0(...) \
FSM FSM::Instance; \
INSTANT \

#define SETUP_FSM_1(Function) \
FSM FSM::Instance(Function); \
INSTANT \

#define FSM_SET(State) State.nextState = true
#define FSM_RESET(State) State.nextState = false

#endif

