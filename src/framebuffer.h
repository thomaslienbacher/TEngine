//
// Created by Thomas Lienbacher on 25.02.2018.
//

#ifndef TENGINE_FRAMEBUFFER_H
#define TENGINE_FRAMEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include "texture.h"

typedef struct _framebuffer_s {
    texture_t *texture;
    int originalWidth;
    int originalHeight;
    int width;
    int height;
    GLuint id;
} framebuffer_t;

framebuffer_t *framebuffer_new(int width, int height);

void framebuffer_bind(framebuffer_t *framebuffer);

void framebuffer_clear(framebuffer_t *framebuffer);

void framebuffer_free(framebuffer_t *framebuffer);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_FRAMEBUFFER_H
