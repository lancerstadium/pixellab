#include "minunit.h"
#include <core/state.h>


StateManager *sm;

char* test_init() {
    sm = StateManager_init();
    mu_assert(sm != NULL, "Failed to init state manager.");
    return NULL;
}


char* test_scale() {
    int cap = sm->capcity;
    StateManager_scale(sm);
    mu_assert(sm->capcity == cap * 2, "Failed to scale state manager.");
    return NULL;
}


unsigned int initState1() {
    mu_msg("state 1 created");
    return 0;
}

unsigned int destroyState1() {
    mu_msg("state 1 destroyed");
    return 0;
}

unsigned int initState2() {
    mu_msg("state 2 created");
    return 0;
}

unsigned int updateState1(float deltatime) {
    mu_msg("state 1/2 update %f", deltatime);
    return 0;
}

unsigned int destroyState2() {
    mu_msg("state 2 destroyed");
    return 0;
}

char* test_push_pop() {
    State s1 = {0};
    s1.init = initState1;
    s1.update = updateState1;
    s1.destory = destroyState1;
    StateManager_push(sm, &s1);
    StateManager_update(sm, 10.0f);

    mu_msg("ss.destory = %p", sm->top->destory);
    sm->top->destory();

    State s2 = {0};
    s2.init = initState2;
    s2.update = updateState1;
    s2.destory = destroyState2;
    StateManager_push(sm, &s2);
    StateManager_update(sm, 10.0f);

    mu_msg("ss.destory = %p", sm->top->destory);

    State* ss = StateManager_pop(sm);
    StateManager_update(sm, 10.0f);

    mu_assert(sm->top == &s1, "Wrong top after pop.");
    mu_assert(ss == &s2, "Wrong state after pop.");
    mu_assert(ss->update == sm->top->update, "Wrong update fn after pop.");
    
    return NULL;
}


char* test_free() {
    mu_msg("ss.destory = %p", sm->top->destory);
    // State* ss = StateManager_pop(sm);
    // mu_msg("ss.destory = %p", ss->destory);
    StateManager_free(sm);
    mu_assert(sm->stack == NULL, "Failed to free state manager.");
    return NULL;
}



char *all_tests() {
    mu_suite_start();

    mu_run_test(test_init);
    mu_run_test(test_scale);
    mu_run_test(test_push_pop);
    mu_run_test(test_free);

    return NULL;
}

RUN_TESTS(all_tests);