//
// Created by Thomas Lienbacher on 25.02.2018.
//

#ifndef TENGINE_INST_MODEL_H
#define TENGINE_INST_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "model.h"

typedef struct {
    mesh_t* mesh;
    texture_t* texture;
    int count;
    mat4x4* mats;
    unsigned int matVbos[4];
} inst_model_t;

inst_model_t* inst_model_new(mesh_t* mesh, texture_t* texture, int count);
void inst_model_update(inst_model_t* inst_model);//pushes mats into the buffer
void inst_model_free(inst_model_t* inst_model);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_INST_MODEL_H
