//
// Created by Thomas Lienbacher on 25.01.2018.
//

/**
 * version: 1.0
 */

#ifndef TENGINE_TEXTURE_H
#define TENGINE_TEXTURE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "master.h"

typedef struct {
    GLuint id;
} texture_t;


texture_t* texture_new(FILE* file, GLenum filter, float aniso);
void texture_bind(texture_t* texture);
void texture_free(texture_t* texture);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_TEXTURE_H
