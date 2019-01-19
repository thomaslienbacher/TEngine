//
// Created by Thomas Lienbacher on 05.02.2018.
//

#include "tengine_math.h"
#include "utils.h"

const vec2 VEC2_ZERO = {0, 0};
const vec3 VEC3_ZERO = {0, 0, 0};
const vec4 VEC4_ZERO = {0, 0, 0, 0};

const vec3 VEC3_UNITX = {1.0f, 0, 0};
const vec3 VEC3_UNITY = {0, 1.0f, 0};
const vec3 VEC3_UNITZ = {0, 0, 1.0f};

void vec2_print(const vec2 v) {
    dprintf("v2: %.6f %.6f\n", v[0], v[1]);
}

void vec3_print(const vec3 v) {
    dprintf("v3: %.6f %.6f %.6f\n", v[0], v[1], v[2]);
}

void vec4_print(const vec4 v) {
    dprintf("v4: %.6f %.6f %.6f %.6f\n", v[0], v[1], v[2], v[3]);
}

void mat4x4_print(const mat4x4 mat) {
    for (int i = 0; i < 4; ++i) {
        dprintf("m4c%d: %.6f %.6f %.6f %.6f\n", i, mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
    }
}