#include "minunit.h"
#include <core/state.h>
#include <core/graphics.h>
#include <SDL.h>

StateManager *sm;
Graphics g;

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

char* test_init() {

    sm = StateManager_create();
    mu_ast(sm != NULL, "Failed to init state manager.");
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        StateManager_free(sm);
        return "Failed to init SDL.";
    }


    if(Graphics_init(&g) != 0) {
        StateManager_free(sm);
        SDL_Quit();
        return "Failed to init graphics.";
    }
    
    return NULL;
}


char* test_loop() {
    State s1 = {0};
    s1.init = initState1;
    s1.update = updateState1;
    s1.destory = destroyState1;
    StateManager_push(sm, &s1);

    int quit = 0;
    SDL_Event e;

    int cnt = 50;
    while(!quit && cnt-- > 0) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        StateManager_update(sm, 10.0f);
    }

    return NULL;
}


char *all_tests() {
    mu_suite_start();

    mu_run_test(test_init);
    mu_run_test(test_loop);

    return NULL;
}

RUN_TESTS(all_tests);