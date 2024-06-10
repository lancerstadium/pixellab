#include <core/state.h>


static int sm_capcity = 10;


StateManager* StateManager_init() {
    StateManager* sm = (StateManager*)malloc(sizeof(StateManager));
    sm->capcity = sm_capcity;
    sm->stack = Stack_create();
    sm->top = NULL;
    return sm;
}

void StateManager_free(StateManager *sm) {
    while(Stack_count(sm->stack) > 0) {
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
    if (StateManager_count(sm) == 0) return NULL; 
    State* s = Stack_pop(sm->stack);
    // if(s && s->destory) s->destory();
    sm->top = Stack_peek(sm->stack);
    printf("cnt = %d, s.destory = %p\n", StateManager_count(sm), s->destory);
    return s;
}


int StateManager_update(StateManager *sm, float delta_time) {
    if(sm->top) {
        sm->top->update(delta_time);
        return 1;
    }
    return 0;
}

int StateManager_draw(StateManager *sm, float delta_time) {
    if(sm->top) {
        sm->top->draw(delta_time);
        return 1;
    }
    return 0;
}