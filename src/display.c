//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "utils.h"
#include "master.h"
#include "filehelper.h"

static void debug_msg_callback(GLenum source, GLenum type, GLuint id,
                      GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    dief("OpenGl Callback: %s type = 0x%x, severity = 0x%x, message = %s\n",
         (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

display_t* display_new(const char* title, int width, int height){
    display_t* display = calloc(1, sizeof(display_t));
    display->running = 1;
    display->lastTick = SDL_GetTicks();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); //to disable aa both need to be set to 0
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); //anti aliasing

    display->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    display->glContext = SDL_GL_CreateContext(display->window);

    SDL_GL_MakeCurrent(display->window, display->glContext);
    SDL_GL_SetSwapInterval(1); // vsync

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if(GLEW_OK != err){
        die((char*)glewGetErrorString(err));
    }

    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

#ifdef DEBUG_BUILD
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC) debug_msg_callback, 0);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif

    return display;
}

void display_set_icon(display_t* display, FILE* icon){
    unsigned error;
    unsigned char* image;
    unsigned width, height;

    unsigned long fileLen = 0;
    char* fileData = NULL;
    fadv_info(icon, &fileLen, &fileData);

    error = lodepng_decode32(&image, &width, &height, (unsigned char*)fileData, fileLen);
    free(fileData);
    if(error) dief("Loading Icon: %s", lodepng_error_text(error));

    display->icon = SDL_CreateRGBSurfaceWithFormatFrom(image, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    SDL_SetWindowIcon(display->window, display->icon);

    free(image);
}

void display_prepare(display_t* display, float* delta){
    while (SDL_PollEvent(&display->events)) {
        if (display->events.type == SDL_QUIT) {
            display->running = 0;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float c = 0;
    glClearColor(c, c, c, 1);

    Uint32 now = SDL_GetTicks();
    *delta = (float)(now - display->lastTick) / 1000.f;
    display->lastTick = now;
}

void display_show(display_t* display){
    SDL_GL_SwapWindow(display->window);
}

void display_free(display_t* display){
    if(display->icon != 0) SDL_FreeSurface(display->icon);
    SDL_GL_MakeCurrent(display->window, NULL);
    SDL_DestroyWindow(display->window);
    SDL_GL_DeleteContext(display->glContext);
    SDL_Quit();

    free(display);
}