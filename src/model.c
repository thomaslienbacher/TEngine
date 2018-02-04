//
// Created by Thomas Lienbacher on 25.01.2018.
//

/**
 * version: 1.0
 */

#include <stdlib.h>
#include "model.h"

model_t* model_new(mesh_t* mesh, texture_t* texture){
    model_t* model = calloc(1, sizeof(model_t));
    model->mesh = mesh;
    model->texture = texture;

    model_mat(model, model->pos, model->rot, model->scale);

    return model;
}

void model_mat(model_t* model, const vec3 pos, const vec3 rot, float scale){
    static mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale, scale, scale);

    static mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate_Y(rotateMat, rotateMat, rot[1] * DEG_2_RAD);
    mat4x4_rotate_Z(rotateMat, rotateMat, rot[2] * DEG_2_RAD);
    mat4x4_rotate_X(rotateMat, rotateMat, rot[0] * DEG_2_RAD);

    static mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], pos[2]);

    mat4x4_identity(model->mat);
    mat4x4_mul(model->mat, model->mat, translateMat);
    mat4x4_mul(model->mat, model->mat, scaleMat);
    mat4x4_mul(model->mat, model->mat, rotateMat);
}

void model_free(model_t* model){
    free(model);
}