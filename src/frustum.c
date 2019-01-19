//
// Created by Thomas Lienbacher on 30.09.2018.
//

#include <stdio.h>
#include "frustum.h"

void frustum_projview(frustum_t frustum, mat4x4 projview) {
    for (int i = 0; i < 4; i++) frustum[0][i] = projview[i][3] + projview[i][0];
    for (int i = 0; i < 4; i++) frustum[1][i] = projview[i][3] - projview[i][0];
    for (int i = 0; i < 4; i++) frustum[2][i] = projview[i][3] - projview[i][1];
    for (int i = 0; i < 4; i++) frustum[3][i] = projview[i][3] + projview[i][1];
    for (int i = 0; i < 4; i++) frustum[4][i] = projview[i][3] + projview[i][2];
    for (int i = 0; i < 4; i++) frustum[5][i] = projview[i][3] - projview[i][2];

    for (int i = 0; i < 6; ++i) {
        float l = 1.0f / vec3_len(frustum[i]);
        for (int a = 0; a < 4; a++) frustum[i][a] *= l;
    }

}

char frustum_ispoint(frustum_t frustum, vec3 p) {
    for (int i = 0; i < 6; i++) {
        float dist = vec3_dot(p, (float[]) {frustum[i][0], frustum[i][1], frustum[i][2]}) + frustum[i][3];
        if (dist < 0) return 0;
    }

    return 1;
}

char frustum_issphere(frustum_t frustum, vec3 p, float radius) {
    for (int i = 0; i < 6; i++) {
        float dist = vec3_dot(p, (float[]) {frustum[i][0], frustum[i][1], frustum[i][2]}) + frustum[i][3] + radius;
        if (dist < 0) return 0;
    }

    return 1;
}
