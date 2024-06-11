#include <SDL.h>
#include <core/graphics.h>

static int graphics_width = 800;
static int graphics_height = 600;

int Graphics_init(Graphics *g) {
    if(!g->windowTitle) g->windowTitle = "[No Title]";
    if(!g->width) g->width = graphics_width;
    if(!g->height) g->height = graphics_height;

    g->window = SDL_CreateWindow(
        g->windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        g->width,
        g->height,
        SDL_WINDOW_SHOWN
    );

    if(g->window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }
    return 0;
};


void Graphics_free(Graphics *g) {
    SDL_DestroyWindow(g->window);
    g->window = NULL;
}