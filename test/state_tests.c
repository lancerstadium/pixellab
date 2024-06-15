#include <sob/sob.h>
#include <core/state.h>


StateManager *sm;

char* test_init() {
    sm = StateManager_create();
    UnitTest_ast(sm != NULL, "Failed to init state manager.");
    return NULL;
}


char* test_scale() {
    int cap = sm->capcity;
    StateManager_scale(sm);
    UnitTest_ast(sm->capcity == cap * 2, "Failed to scale state manager.");
    return NULL;
}


unsigned int initState1() {
    UnitTest_msg("state 1 created");
    return 0;
}

unsigned int destroyState1() {
    UnitTest_msg("state 1 destroyed");
    return 0;
}

unsigned int initState2() {
    UnitTest_msg("state 2 created");
    return 0;
}

unsigned int updateState1(float deltatime) {
    UnitTest_msg("state 1/2 update %f", deltatime);
    return 0;
}

unsigned int destroyState2() {
    UnitTest_msg("state 2 destroyed");
    return 0;
}

char* test_push_pop() {
    State s1 = {0};
    s1.init = initState1;
    s1.update = updateState1;
    s1.destory = destroyState1;
    StateManager_push(sm, &s1);
    StateManager_update(sm, 10.0f);

    UnitTest_msg("ss.destory = %p", sm->top->destory);
    sm->top->destory();

    State s2 = {0};
    s2.init = initState2;
    s2.update = updateState1;
    s2.destory = destroyState2;
    StateManager_push(sm, &s2);
    StateManager_update(sm, 10.0f);

    UnitTest_msg("ss.destory = %p", sm->top->destory);

    State* ss = StateManager_pop(sm);
    StateManager_update(sm, 11.0f);

    UnitTest_ast(sm->top == &s1, "Wrong top after pop.");
    UnitTest_ast(ss == &s2, "Wrong state after pop.");
    UnitTest_ast(ss->update == sm->top->update, "Wrong update fn after pop.");
    UnitTest_ast(StateManager_count(sm) == 1, "Wrong count after pop.");

    ss = StateManager_pop(sm);
    StateManager_update(sm, 12.0f);
    UnitTest_ast(sm->top == NULL, "Wrong top after pop.");
    UnitTest_ast(StateManager_count(sm) == 0, "Wrong count after pop.");
    
    return NULL;
}


char* test_free() {
    
    StateManager_free(sm);
    UnitTest_ast(sm->stack == NULL, "Failed to free state manager.");
    return NULL;
}



char *all_tests() {
    

    UnitTest_add(test_init);
    UnitTest_add(test_scale);
    UnitTest_add(test_push_pop);
    UnitTest_add(test_free);

    return NULL;
}

UnitTest_run(all_tests);