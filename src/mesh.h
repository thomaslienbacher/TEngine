//
// Created by Thomas Lienbacher on 20.01.2018.
//

#ifndef TENGINE_MESH_H
#define TENGINE_MESH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include <stdio.h>

#define POSITION_INDEX 0
#define TEXCOORD_INDEX 1
#define NORMAL_INDEX 2
#define MODELICOL1_INDEX 3
#define QUAD_SIZE 6

typedef struct _mesh_s {
    GLuint vao;
    GLuint vbos[4];
    unsigned int numElements;
} mesh_t;

typedef struct _quad_s {
    GLuint vao;
    GLuint vbos[2];//vertices, texcoords
} quad_t;

mesh_t *mesh_newobjf(FILE *objFile);

mesh_t *mesh_newobj(const char *objFile);

mesh_t *mesh_newdata(unsigned int numIndices, unsigned int *indices, unsigned int numVertices,
                     float *vertices, float *texcoords, float *normals);

void mesh_bind(mesh_t *mesh);

void mesh_free(mesh_t *mesh);


void vao_add_vbo(GLuint *vbos, int vbo, int size, const float *data, unsigned int len, unsigned int index);

void vao_bind(GLuint vao);


quad_t *quad_new();

void quad_free(quad_t *quad);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_MESH_H
