//
// Created by Thomas Lienbacher on 20.01.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "utils.h"
#include "filehelper.h"
#include "render.h"
#include "framebuffer.h"

static void debug_msg_callback(GLenum source, GLenum type, GLuint id,
                      GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if(type == GL_DEBUG_TYPE_ERROR) {
       dief("OpenGl Callback: ** GL ERROR ** type = 0x%x, severity = 0x%x, message = %s\n", type, severity, message);
    }
    else {
        dprintf("OpenGl Callback: INFO type = 0x%x, severity = 0x%x, message = %s\n", type, severity, message);
    }
}

display_t *display_new(const char *title, int width, int height, char fullscreen, float renderSize) {
    display_t* display = calloc(1, sizeof(display_t));
    display->running = 1;
    display->hasFocus = 1;
    display->lastTick = 0;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0); //to disable aa both need to be set to 0
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0); //anti aliasing
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

#ifdef DEBUG_BUILD
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, 0);
#endif

    Uint32 flags = SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

    if(fullscreen) {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);
        width = dm.w;
        height = dm.h;
    }

    display->width = width;
    display->height = height;
    display->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
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
    if(strstr((char*)glGetString(GL_VENDOR), "NVIDIA")) { //I can't get debug output to work on nvidia so I'll guess
        dprintf("Your graphics card vendor is %s.\n"
                        "For reason debug output doesn't work with their GPUs.\n", (char*) glGetString(GL_VENDOR));
    }
    else {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback((GLDEBUGPROC) debug_msg_callback, 0);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }
#endif

    _render_init_quadshader();

    if(renderSize <= 0) dief("Display: renderSize is too small: %f", renderSize);
    display->renderTarget = framebuffer_new((int)lroundf(width * renderSize), (int)lroundf(height * renderSize));
    framebuffer_bind(display->renderTarget);

    return display;
}

void display_set_iconf(display_t *display, FILE *icon){
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

void display_set_icon(display_t *display, const char* icon) {
    FILE* f = fadv_open(icon, "rb");
    display_set_iconf(display, f);
    fadv_close(f);
}

void display_prepare(display_t *display, float *delta, float renderSize) {
    while (SDL_PollEvent(&display->events)) {
        if (display->events.type == SDL_QUIT) {
            display->running = 0;
        }
        if(display->events.type == SDL_WINDOWEVENT){
            if(display->events.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) display->hasFocus = 1;
            if(display->events.window.event == SDL_WINDOWEVENT_FOCUS_LOST) display->hasFocus = 0;
        }
    }

    glClearColor(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Uint32 now = SDL_GetTicks();
    *delta = (float)(now - display->lastTick) / 1000.f;
    display->lastTick = now;

    if(renderSize <= 0) dief("Display: renderSize is too small: %f", renderSize);
    display->renderTarget->width = (int)lroundf(display->width * renderSize);
    display->renderTarget->height = (int)lroundf(display->height * renderSize);

    framebuffer_bind(display->renderTarget);
    framebuffer_clear(display->renderTarget);
}

inline void display_as_target(display_t* display) {
    framebuffer_bind(display->renderTarget);
}

void display_show(display_t* display){
    framebuffer_bind(NULL);
    glViewport(0, 0, display->width, display->height);

    GLint curReadFbo;
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &curReadFbo);

    if(curReadFbo != display->renderTarget->id) glBindFramebuffer(GL_READ_FRAMEBUFFER, display->renderTarget->id);
    glBlitFramebuffer(0, 0, display->renderTarget->width, display->renderTarget->height,
                      0, 0, display->width, display->height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    SDL_GL_SwapWindow(display->window);
}

void display_free(display_t* display){
    _render_quit_quadshader();

    framebuffer_free(display->renderTarget);
    if(display->icon != 0) SDL_FreeSurface(display->icon);
    SDL_GL_MakeCurrent(display->window, NULL);
    SDL_DestroyWindow(display->window);
    SDL_GL_DeleteContext(display->glContext);
    SDL_Quit();

    free(display);
}