#include <util/sob.h>
#include <core/state.h>


StateManager *sm;

char* test_init() {
    sm = StateManager_create();
    ut_ast(sm != NULL, "Failed to init state manager.");
    return NULL;
}


char* test_scale() {
    int cap = sm->capcity;
    StateManager_scale(sm);
    ut_ast(sm->capcity == cap * 2, "Failed to scale state manager.");
    return NULL;
}


unsigned int initState1() {
    ut_msg("state 1 created");
    return 0;
}

unsigned int destroyState1() {
    ut_msg("state 1 destroyed");
    return 0;
}

unsigned int initState2() {
    ut_msg("state 2 created");
    return 0;
}

unsigned int updateState1(float deltatime) {
    ut_msg("state 1/2 update %f", deltatime);
    return 0;
}

unsigned int destroyState2() {
    ut_msg("state 2 destroyed");
    return 0;
}

char* test_push_pop() {
    State s1 = {0};
    s1.init = initState1;
    s1.update = updateState1;
    s1.destory = destroyState1;
    StateManager_push(sm, &s1);
    StateManager_update(sm, 10.0f);

    ut_msg("ss.destory = %p", sm->top->destory);
    sm->top->destory();

    State s2 = {0};
    s2.init = initState2;
    s2.update = updateState1;
    s2.destory = destroyState2;
    StateManager_push(sm, &s2);
    StateManager_update(sm, 10.0f);

    ut_msg("ss.destory = %p", sm->top->destory);

    State* ss = StateManager_pop(sm);
    StateManager_update(sm, 11.0f);

    ut_ast(sm->top == &s1, "Wrong top after pop.");
    ut_ast(ss == &s2, "Wrong state after pop.");
    ut_ast(ss->update == sm->top->update, "Wrong update fn after pop.");
    ut_ast(StateManager_count(sm) == 1, "Wrong count after pop.");

    ss = StateManager_pop(sm);
    StateManager_update(sm, 12.0f);
    ut_ast(sm->top == NULL, "Wrong top after pop.");
    ut_ast(StateManager_count(sm) == 0, "Wrong count after pop.");
    
    return NULL;
}


char* test_free() {
    
    StateManager_free(sm);
    ut_ast(sm->stack == NULL, "Failed to free state manager.");
    return NULL;
}



char *all_tests() {
    

    ut_add(test_init);
    ut_add(test_scale);
    ut_add(test_push_pop);
    ut_add(test_free);

    return NULL;
}

ut_run(all_tests);