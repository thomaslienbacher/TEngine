//
// Created by Thomas Lienbacher on 25.02.2018.
//

#include <stdlib.h>
#include "inst_model.h"

inst_model_t* inst_model_new(mesh_t* mesh, texture_t* texture,  int count) {
    inst_model_t* inst_model = calloc(1, sizeof(inst_model_t));
    inst_model->mesh = mesh;
    inst_model->texture = texture;
    inst_model->count = count;
    inst_model->mats = calloc((size_t)count, sizeof(mat4x4));

    for (int i = 0; i < count; ++i) {
        mat4x4_identity(inst_model->mats[i]);
    }

    mesh_bind(mesh);
    glGenBuffers(4, inst_model->matVbos);

    for (unsigned int i = 0; i < 4; ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, inst_model->matVbos[i]);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float) * 16, inst_model->mats, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(MODELICOL1_INDEX + i, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * i * sizeof(float)));
        glVertexAttribDivisor(MODELICOL1_INDEX + i, 1);
    }

    return inst_model;
}

void inst_model_update(inst_model_t* inst_model) {
    mesh_bind(inst_model->mesh);

    for (unsigned int i = 0; i < 4; ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, inst_model->matVbos[i]);
        glBufferData(GL_ARRAY_BUFFER, inst_model->count * sizeof(float) * 16, inst_model->mats, GL_DYNAMIC_DRAW);
    }
}

void inst_model_free(inst_model_t* inst_model) {
    mesh_bind(inst_model->mesh);
    glDeleteBuffers(4, inst_model->matVbos);
    free(inst_model->mats);
    free(inst_model);
}