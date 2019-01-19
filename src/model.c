//
// Created by Thomas Lienbacher on 25.01.2018.
//

#include <stdlib.h>
#include "model.h"

model_t *model_new(mesh_t *mesh, texture_t *texture) {
    model_t *model = calloc(1, sizeof(model_t));
    model->mesh = mesh;
    model->texture = texture;
    vec3_set(model->scale, 1.f, 1.f, 1.f);

    model_transform(model, model->pos, model->rot, *model->scale);

    return model;
}

void model_transform(model_t *model, const vec3 pos, const vec3 rot, float scale) {
    mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale, scale, scale);

    mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate_Y(rotateMat, rotateMat, rot[1] * DEG_2_RAD);
    mat4x4_rotate_Z(rotateMat, rotateMat, rot[2] * DEG_2_RAD);
    mat4x4_rotate_X(rotateMat, rotateMat, rot[0] * DEG_2_RAD);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], pos[2]);

    mat4x4_mul(model->mat, translateMat, scaleMat);
    mat4x4_mul(model->mat, model->mat, rotateMat);
}

void model_transform_as(model_t *model, const vec3 pos, const vec3 rot, const vec3 scale) {
    mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale[0], scale[1], scale[2]);

    mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate_Y(rotateMat, rotateMat, rot[1] * DEG_2_RAD);
    mat4x4_rotate_Z(rotateMat, rotateMat, rot[2] * DEG_2_RAD);
    mat4x4_rotate_X(rotateMat, rotateMat, rot[0] * DEG_2_RAD);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], pos[2]);

    mat4x4_mul(model->mat, translateMat, scaleMat);
    mat4x4_mul(model->mat, model->mat, rotateMat);
}

void model_transformd(mat4x4 mat, const vec3 pos, const vec3 rot, float scale) {
    mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale, scale, scale);

    mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate_Y(rotateMat, rotateMat, rot[1] * DEG_2_RAD);
    mat4x4_rotate_Z(rotateMat, rotateMat, rot[2] * DEG_2_RAD);
    mat4x4_rotate_X(rotateMat, rotateMat, rot[0] * DEG_2_RAD);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], pos[2]);

    mat4x4_mul(mat, translateMat, scaleMat);
    mat4x4_mul(mat, mat, rotateMat);
}

void model_transformd_as(mat4x4 mat, const vec3 pos, const vec3 rot, const vec3 scale) {
    mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale[0], scale[1], scale[2]);

    mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate_Y(rotateMat, rotateMat, rot[1] * DEG_2_RAD);
    mat4x4_rotate_Z(rotateMat, rotateMat, rot[2] * DEG_2_RAD);
    mat4x4_rotate_X(rotateMat, rotateMat, rot[0] * DEG_2_RAD);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], pos[2]);

    mat4x4_mul(mat, translateMat, scaleMat);
    mat4x4_mul(mat, mat, rotateMat);
}

void model_free(model_t *model) {
    free(model);
}

inst_model_t *inst_model_new(mesh_t *mesh, texture_t *texture, int count) {
    inst_model_t *inst_model = calloc(1, sizeof(inst_model_t));
    inst_model->mesh = mesh;
    inst_model->texture = texture;
    inst_model->count = count;
    inst_model->mats = calloc((size_t) count, sizeof(mat4x4));

    for (int i = 0; i < count; ++i) {
        mat4x4_identity(inst_model->mats[i]);
    }

    mesh_bind(mesh);
    glGenBuffers(4, inst_model->matVbos);

    for (unsigned int i = 0; i < 4; ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, inst_model->matVbos[i]);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float) * 16, inst_model->mats, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(MODELICOL1_INDEX + i, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float),
                              (void *) (4 * i * sizeof(float)));
        glVertexAttribDivisor(MODELICOL1_INDEX + i, 1);
    }

    return inst_model;
}

void inst_model_update(inst_model_t *inst_model) {
    mesh_bind(inst_model->mesh);

    for (unsigned int i = 0; i < 4; ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, inst_model->matVbos[i]);
        glBufferData(GL_ARRAY_BUFFER, inst_model->count * sizeof(float) * 16, inst_model->mats, GL_DYNAMIC_DRAW);
    }
}

void inst_model_free(inst_model_t *inst_model) {
    glDeleteBuffers(4, inst_model->matVbos);
    free(inst_model->mats);
    free(inst_model);
}

quad_model_t *quad_model_new(texture_t *texture, float x, float y, float width, float height, float rot) {
    quad_model_t *quad_model = calloc(1, sizeof(quad_model_t));
    quad_model->quad = quad_new();
    quad_model->texture = texture;
    quad_model->dim[0] = x;
    quad_model->dim[1] = y;
    quad_model->dim[2] = width;
    quad_model->dim[3] = height;
    quad_model->rot = rot;

    return quad_model;
}

void quad_model_free(quad_model_t *quad_model) {
    quad_free(quad_model->quad);
    free(quad_model);
}