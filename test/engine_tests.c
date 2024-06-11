#include "minunit.h"
#include <core/state.h>
#include <core/graphics.h>
#include <core/engine.h>
#include <SDL.h>



unsigned int initState1() {
    mu_msg("state 1 created");
    return 0;
}
unsigned int updateState1(float dt) {
    mu_msg("state 1 updated: %f", dt);
    return 0;
}
unsigned int destroyState1() {
    mu_msg("state 1 destroyed");
    return 0;
}


char* test_loop() {

    Engine *eng;

    EngineOption option = {0};
    option.title = "Test Engine";
    option.width = 480;
    option.height = 272;
    eng = malloc(sizeof(Engine));
    Engine_init(eng, &option);
    mu_ast(eng->graphics.width == option.width, "Failed to set width.");

    State s1 = {0};
    s1.init = initState1;
    s1.update = updateState1;
    s1.destory = destroyState1;
    StateManager_push(&eng->statemanager, &s1);
    mu_ast(StateManager_count(&eng->statemanager) == 1, "Wrong count after push.");
    mu_ast(eng->statemanager.top->update == updateState1, "Wrong update fn after push.");

    SDL_Event e;
    while(!eng->quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) eng->quit = 1;
        }
        StateManager_update(&eng->statemanager, 10.0f);
    }


    Engine_free(eng);
    mu_ast(eng->graphics.window == NULL, "Failed to free window.");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_loop);

    return NULL;
}

RUN_TESTS(all_tests);