//
// Created by Thomas Lienbacher on 30.09.2018.
//

#include <stdio.h>
#include "frustum.h"

void frustum_projview(frustum_t frustum, mat4x4 proj, mat4x4 view) {
    mat4x4 combo;
    mat4x4 transposeView;

    mat4x4_transpose(transposeView, view);
    mat4x4_mul(combo, proj, transposeView);
    //mat4x4_dup(combo, proj);

    for (int i = 0; i < 4; i++) frustum[0][i] = combo[3][i] + combo[0][i];
    for (int i = 0; i < 4; i++) frustum[1][i] = combo[3][i] - combo[0][i];
    for (int i = 0; i < 4; i++) frustum[2][i] = combo[3][i] - combo[1][i];
    for (int i = 0; i < 4; i++) frustum[3][i] = combo[3][i] + combo[1][i];
    for (int i = 0; i < 4; i++) frustum[4][i] = combo[3][i] + combo[2][i];
    for (int i = 0; i < 4; i++) frustum[5][i] = combo[3][i] - combo[2][i];

    /*frustum[0][0] = combo[3][0] + combo[0][0];
    frustum[0][1] = combo[3][1] + combo[0][1];
    frustum[0][2] = combo[3][2] + combo[0][2];
    frustum[0][3] = combo[3][3] + combo[0][3];

    frustum[1][0] = combo[3][0] - combo[0][0];
    frustum[1][1] = combo[3][1] - combo[0][1];
    frustum[1][2] = combo[3][2] - combo[0][2];
    frustum[1][3] = combo[3][3] - combo[0][3];

    frustum[2][0] = combo[3][0] - combo[1][0];
    frustum[2][1] = combo[3][1] - combo[1][1];
    frustum[2][2] = combo[3][2] - combo[1][2];
    frustum[2][3] = combo[3][3] - combo[1][3];

    frustum[3][0] = combo[3][0] + combo[1][0];
    frustum[3][1] = combo[3][1] + combo[1][1];
    frustum[3][2] = combo[3][2] + combo[1][2];
    frustum[3][3] = combo[3][3] + combo[1][3];

    frustum[4][0] = combo[3][0] + combo[2][0];
    frustum[4][1] = combo[3][1] + combo[2][1];
    frustum[4][2] = combo[3][2] + combo[2][2];
    frustum[4][3] = combo[3][3] + combo[2][3];

    frustum[5][0] = combo[3][0] - combo[2][0];
    frustum[5][1] = combo[3][1] - combo[2][1];
    frustum[5][2] = combo[3][2] - combo[2][2];
    frustum[5][3] = combo[3][3] - combo[2][3];*/

    for (int i = 0; i < 6; ++i) {
        vec3_norm(frustum[i], frustum[i]);
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
    return 0;
}
