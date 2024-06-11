#include <SDL.h>
#include <core/state.h>
#include <core/graphics.h>
#include <core/engine.h>


int Engine_init(Engine *e, EngineOption *option) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if(option != NULL) {
        e->graphics.width = option->width;
        e->graphics.height = option->height;
        e->graphics.windowTitle = option->title;
    }

    Graphics_init(&e->graphics);
    StateManager_init(&e->statemanager);
    e->quit = 0;

    return 0;
}


void Engine_free(Engine *e) {
    StateManager_free(&e->statemanager);
    Graphics_free(&e->graphics);

    SDL_Quit();
}