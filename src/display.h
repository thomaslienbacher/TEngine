//
// Created by Thomas Lienbacher on 20.01.2018.
//

#ifndef TENGINE_DISPLAY_H
#define TENGINE_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "master.h"
#include "framebuffer.h"
#include "model.h"

typedef struct _display_s {
    SDL_Window *window;
    SDL_Event events;
    SDL_GLContext glContext;
    SDL_Surface *icon;
    char running;
    char hasFocus;
    Uint32 lastTick;
    framebuffer_t *renderTarget;
    int width;
    int height;
} display_t;

display_t *display_new(const char *title, int width, int height, char fullscreen, float renderScale, char vsync);

void display_set_iconf(display_t *display, FILE *icon);

void display_set_icon(display_t *display, const char *icon);

void display_prepare(display_t *display, float *delta, float renderScale);

void display_as_target(display_t *display);

void display_show(display_t *display);

void display_free(display_t *display);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_DISPLAY_H
