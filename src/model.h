//
// Created by Thomas Lienbacher on 25.01.2018.
//

/**
 * version: 1.0
 */

#ifndef TENGINE_MODEL_H
#define TENGINE_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include "linmath.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"

typedef struct {
    mesh_t* mesh;
    texture_t* texture;
    mat4x4 mat;
    vec3 pos;
    vec3 rot;
    float scale;
} model_t;

model_t* model_new(mesh_t* mesh, texture_t* texture);
void model_mat(model_t* model, const vec3 pos, const vec3 rot, float scale);
void model_free(model_t* model);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_MODEL_H
