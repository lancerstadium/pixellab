#include <core/state.h>

static int statemanager_capcity = 10;


StateManager* StateManager_create() {
    StateManager* sm;
    sm = (StateManager*)malloc(sizeof(StateManager));
    StateManager_init(sm);
    return sm;
}

int StateManager_init(StateManager *sm) {
    sm->capcity = statemanager_capcity;
    sm->stack = Stack_create();
    sm->top = NULL;
    return 0;
}

void StateManager_free(StateManager *sm) {
    while(sm->top != NULL) {
        StateManager_pop(sm);
    }
    sm->stack = NULL;
    sm->top = NULL;
}

void StateManager_scale(StateManager *sm) {
    sm->capcity *= 2;
}

int StateManager_count(StateManager *sm) {
    return Stack_count(sm->stack);
}


void StateManager_push(StateManager *sm, State *s) {
    if(StateManager_count(sm) + 1 == sm->capcity) {
        StateManager_scale(sm);
    }
    Stack_push(sm->stack, s);
    if (s && s->init) s->init();
    sm->top = Stack_peek(sm->stack);
}


State* StateManager_pop(StateManager *sm) {
    if (StateManager_count(sm) == 0) { sm->top = NULL; return NULL; }
    State* s = Stack_pop(sm->stack);
    if(s && s->destory) s->destory();
    sm->top = Stack_peek(sm->stack);
    return s;
}


int StateManager_update(StateManager *sm, float delta_time) {
    if(sm->top) {
        if(sm->top->update) sm->top->update(delta_time);
        return 0;
    }
    return 1;
}

int StateManager_draw(StateManager *sm, float delta_time) {
    if(sm->top) {
        sm->top->draw(delta_time);
        return 0;
    }
    return 1;
}