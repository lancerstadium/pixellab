#ifndef _Core_Engine_h_
#define _Core_Engine_h_


#include <core/graphics.h>
#include <core/state.h>


typedef struct {
    char *title;
    int width;
    int height;
} EngineOption;


typedef struct {
    char quit;
    Graphics graphics;
    StateManager statemanager;
} Engine;


int Engine_init(Engine *e, EngineOption *option);
void Engine_free(Engine *e);


#endif