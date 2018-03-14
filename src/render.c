//
// Created by Thomas Lienbacher on 22.01.2018.
//

/**
 * version: 1.1
 */

#include "render.h"
#include "model.h"
#include "mesh.h"

vec4 CLEAR_COLOR = {0, 0, 0, 0};

const char* QUAD_VERTEX_SHADER = R"(
#version 330

layout(location = 0) in vec2 i_vertex;

uniform vec4 u_transform;//x, y, width, height

out vec2 v_texcoord;

void main() {
    vec4 p = vec4(i_vertex, 0, 1);
    p.x *= u_transform.z * 2;
    p.y *= u_transform.w * 2;
    p.x += u_transform.x - 1 * u_transform.z;
    p.y += u_transform.y - 1 * u_transform.w;

    gl_Position = p;
    v_texcoord = i_vertex;
}
)";

const char* QUAD_FRAGMENT_SHADER = R"(
#version 330

in vec2 v_texcoord;

uniform sampler2D sampler;

out vec4 o_color;

void main(){
    o_color = texture(sampler, v_texcoord);
}
)";

program_t* QUAD_SHADER = NULL;

//users should call this
void _render_init() {
    QUAD_SHADER = program_news(QUAD_VERTEX_SHADER, QUAD_FRAGMENT_SHADER);
}

void _render_quit() {
    program_free(QUAD_SHADER);
}

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

void render_instanced_dyn(model_t *model, program_t *program, int count, mat4x4 *mats){
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

void render_inst_model(inst_model_t* inst_model, program_t *program) {
    mesh_bind(inst_model->mesh);
    texture_bind(inst_model->texture);

    //enable instancing
    int loc = program_getunipos(program, "u_instanced");
    program_unipos_f(program, loc, 1);

    glEnableVertexAttribArray(POSITION_INDEX);
    glEnableVertexAttribArray(TEXCOORD_INDEX);
    glEnableVertexAttribArray(NORMAL_INDEX);
    for (unsigned int j = 0; j < 4; ++j) {
        glEnableVertexAttribArray(MODELICOL1_INDEX + j);
    }
    glActiveTexture(GL_TEXTURE0);

    glDrawElementsInstanced(GL_TRIANGLES, inst_model->mesh->numElements, GL_UNSIGNED_INT, 0, inst_model->count);

    glDisableVertexAttribArray(POSITION_INDEX);
    glDisableVertexAttribArray(TEXCOORD_INDEX);
    glDisableVertexAttribArray(NORMAL_INDEX);
    for (unsigned int j = 0; j < 4; ++j) {
        glDisableVertexAttribArray(MODELICOL1_INDEX + j);
    }

    //disable instancing
    program_unipos_f(program, loc, 0);
}

void render_quad(quad_model_t* quad_model) {
    mesh_bind((mesh_t*)quad_model->quad);
    texture_bind(quad_model->texture);
    program_unistr_vec4(QUAD_SHADER, "u_transform", quad_model->dim);

    glEnableVertexAttribArray(POSITION_INDEX);
    glActiveTexture(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, QUAD_SIZE);

    glDisableVertexAttribArray(POSITION_INDEX);
}

void render_end(){
    glDisableVertexAttribArray(POSITION_INDEX);
    glDisableVertexAttribArray(TEXCOORD_INDEX);
    glDisableVertexAttribArray(NORMAL_INDEX);
}