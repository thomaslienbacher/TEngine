//
// Created by Thomas Lienbacher on 22.01.2018.
//

/**
 * version: 1.1
 */

#include "render.h"

void render_begin(){
    glEnableVertexAttribArray(POSITION_INDEX);
    glEnableVertexAttribArray(TEXCOORD_INDEX);
    glEnableVertexAttribArray(NORMAL_INDEX);
    glActiveTexture(GL_TEXTURE0);
}

void render_model(model_t* model){
    mesh_bind(model->mesh);
    texture_bind(model->texture);
    render_begin();
    glDrawElements(GL_TRIANGLES, model->mesh->numElements, GL_UNSIGNED_INT, 0);
    render_end();
}

void render_same_model(model_t* model){
    glDrawElements(GL_TRIANGLES, model->mesh->numElements, GL_UNSIGNED_INT, 0);
}

void render_instanced(model_t* model, program_t* program, int count, mat4x4* mats){
    mesh_bind(model->mesh);
    texture_bind(model->texture);

    //enable instancing
    int loc = program_getunipos(program, "u_instanced");
    program_unipos_f(program, loc, 1);

    unsigned int matVbos[4];
    glGenBuffers(4, matVbos);

    for (unsigned int i = 0; i < 4; ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, matVbos[i]);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float) * 16, mats, GL_STATIC_DRAW);
        glVertexAttribPointer(MODELICOL1_INDEX + i, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * i * sizeof(float)));
        glVertexAttribDivisor(MODELICOL1_INDEX + i, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glEnableVertexAttribArray(POSITION_INDEX);
    glEnableVertexAttribArray(TEXCOORD_INDEX);
    glEnableVertexAttribArray(NORMAL_INDEX);
    for (unsigned int j = 0; j < 4; ++j) {
        glEnableVertexAttribArray(MODELICOL1_INDEX + j);
    }
    glActiveTexture(GL_TEXTURE0);

    glDrawElementsInstanced(GL_TRIANGLES, model->mesh->numElements, GL_UNSIGNED_INT, 0, count);

    glDisableVertexAttribArray(POSITION_INDEX);
    glDisableVertexAttribArray(TEXCOORD_INDEX);
    glDisableVertexAttribArray(NORMAL_INDEX);
    for (unsigned int j = 0; j < 4; ++j) {
        glDisableVertexAttribArray(MODELICOL1_INDEX + j);
    }

    glDeleteBuffers(4, matVbos);

    //disable instancing
    program_unipos_f(program, loc, 0);
}

void render_end(){
    glDisableVertexAttribArray(POSITION_INDEX);
    glDisableVertexAttribArray(TEXCOORD_INDEX);
    glDisableVertexAttribArray(NORMAL_INDEX);
}