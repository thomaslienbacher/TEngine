//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.0
 */

#ifndef TENGINE_DISPLAY_H
#define TENGINE_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"

typedef struct {
    SDL_Window *window;
    SDL_Event events;
    SDL_GLContext glContext;
    SDL_Surface* icon;
    char running;
    Uint32 lastTick;
} display_t;

display_t* display_new(const char* title, int width, int height);
void display_set_icon(display_t* display, FILE* icon);
void display_prepare(display_t* display, float* delta);
void display_show(display_t* display);
void display_free(display_t* display);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_DISPLAY_H
