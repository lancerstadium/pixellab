
#ifndef _Core_Graphics_h_
#define _Core_Graphics_h_

typedef struct {
    char *windowTitle;
    int width;
    int height;
    void *window;
} Graphics;


int Graphics_init(Graphics *g);
void Graphics_free(Graphics *g);


#endif