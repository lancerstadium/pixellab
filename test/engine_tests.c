#include <sob/sob.h>
#include <core/state.h>
#include <core/graphics.h>
#include <core/engine.h>
#include <SDL.h>



unsigned int initState1() {
    UnitTest_msg("state 1 created");
    return 0;
}
unsigned int updateState1(float dt) {
    UnitTest_msg("state 1 updated: %f", dt);
    return 0;
}
unsigned int destroyState1() {
    UnitTest_msg("state 1 destroyed");
    return 0;
}


UnitTest_fn_def(test_loop) {

    Engine *eng;

    EngineOption option = {0};
    option.title = "Test Engine";
    option.width = 480;
    option.height = 272;
    eng = malloc(sizeof(Engine));
    Engine_init(eng, &option);
    UnitTest_ast(eng->graphics.width == option.width, "Failed to set width.");

    State s1 = {0};
    s1.init = initState1;
    s1.update = updateState1;
    s1.destory = destroyState1;
    StateManager_push(&eng->statemanager, &s1);
    UnitTest_ast(StateManager_count(&eng->statemanager) == 1, "Wrong count after push.");
    UnitTest_ast(eng->statemanager.top->update == updateState1, "Wrong update fn after push.");

    SDL_Event e;
    while(!eng->quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) eng->quit = 1;
        }
        StateManager_update(&eng->statemanager, 10.0f);
    }


    Engine_free(eng);
    UnitTest_ast(eng->graphics.window == NULL, "Failed to free window.");

    return NULL;
}

UnitTest_fn_def(all_tests) {

    // UnitTest_add(test_loop);

    return NULL;
}

UnitTest_run(all_tests);