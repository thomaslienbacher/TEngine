//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.0
 */

#ifndef TENGINE_UTILS_H
#define TENGINE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "linmath.h"

//from https://www.rapidtables.com/convert/number/how-radians-to-degrees.html
#define RAD_2_DEG 57.295779513f
#define DEG_2_RAD 0.01745329252f

static inline void mat4x4_cpy(mat4x4 a, mat4x4 b){
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            a[i][j] = b[i][j];
}

static inline void vec3_cpy(vec3 a, const vec3 b){
    for (int i = 0; i < 3; ++i) a[i] = b[i];
}

static inline void vec4_cpy(vec4 a, const vec4 b){
    for (int i = 0; i < 4; ++i) a[i] = b[i];
}

void model_mat_mat(mat4x4 mat, const vec3 pos, const vec3 rot, float scale);

void printmat(mat4x4 mat);

void _die(const char* msg, const char* file, const char* function, int line, const char* date, const char* time);
void _dief(const char* time, const char* file, const char* function, int line, const char* date, const char* format, ...);

#define die(msg) _die(msg, __FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__)
#define dief(msg, ...) _dief(__TIME__, __FILE__, __FUNCTION__, __LINE__, __DATE__, msg, __VA_ARGS__)

#ifdef DEBUG_BUILD
#define dprintf(format, ...) \
{\
    printf(format, __VA_ARGS__);\
}
#else
#define dprintf
#endif

#ifdef __cplusplus
}
#endif

#endif //TENGINE_UTILS_H
