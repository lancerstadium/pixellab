
#ifndef _Core_State_h_
#define _Core_State_h_

#include <utils/stack.h>

typedef unsigned int (*fnPtr)();
typedef unsigned int (*fnPtrFl)(float);


typedef struct {
    fnPtr init;
    fnPtr destory;
    fnPtrFl draw;
    fnPtrFl update;
} State;


typedef struct {
    Stack *stack;
    State *top;
    int capcity;
} StateManager;


StateManager* StateManager_create();
int StateManager_init(StateManager *sm);
void StateManager_free(StateManager *sm);
void StateManager_scale(StateManager *sm);
int StateManager_count(StateManager *sm);
void StateManager_push(StateManager *sm, State *s);
State* StateManager_pop(StateManager *sm);
int StateManager_update(StateManager *sm, float delta_time);
int StateManager_draw(StateManager *sm, float delta_time);


#endif