//
// Created by Thomas Lienbacher on 25.01.2018.
//

#ifndef TENGINE_TEXTURE_H
#define TENGINE_TEXTURE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "master.h"

typedef struct _texture_s {
    int width;
    int height;
    GLuint id;
} texture_t;

texture_t *texture_newf(FILE *file, GLenum filter, float aniso);

texture_t *texture_new(const char *file, GLenum filter, float aniso);

void texture_wrap(texture_t *texture, GLint wrap);

void texture_bind(texture_t *texture);

void texture_free(texture_t *texture);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_TEXTURE_H
