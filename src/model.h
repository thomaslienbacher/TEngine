//
// Created by Thomas Lienbacher on 25.01.2018.
//

/**
 * version: 1.1
 */

#ifndef TENGINE_MODEL_H
#define TENGINE_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include "tengine_math.h"
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

typedef struct {
    mesh_t* mesh;
    texture_t* texture;
    int count;
    mat4x4* mats;
    unsigned int matVbos[4];
} inst_model_t;

model_t* model_new(mesh_t* mesh, texture_t* texture);
void model_mat(model_t* model, const vec3 pos, const vec3 rot, float scale);
void model_mat_mat(mat4x4 mat, const vec3 pos, const vec3 rot, float scale);
void model_free(model_t* model);

inst_model_t* inst_model_new(mesh_t* mesh, texture_t* texture, int count);
void inst_model_update(inst_model_t* inst_model);//pushes mats into the buffer
void inst_model_free(inst_model_t* inst_model);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_MODEL_H
