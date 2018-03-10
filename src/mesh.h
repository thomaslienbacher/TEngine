//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.1
 */

#ifndef TENGINE_MESH_H
#define TENGINE_MESH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <GL/glew.h>
#include <stdio.h>

#define POSITION_INDEX 0
#define TEXCOORD_INDEX 1
#define NORMAL_INDEX 2
#define MODELICOL1_INDEX 3

typedef struct {
    GLuint vao;
    GLuint vbos[4];
    unsigned int numElements;
    unsigned int* elements;
} mesh_t;

typedef struct {
    GLuint vao;
    GLuint vbo;
} quad_t;

mesh_t* mesh_newobjf(FILE *objFile);
mesh_t* mesh_newobj(const char *objFile);
mesh_t* mesh_newdata(unsigned int numIndices, unsigned int* indices, unsigned int numVertices,
                     float* vertices, float* texcoords, float* normals);
void mesh_bind(mesh_t* mesh);
void mesh_free(mesh_t* mesh);

quad_t* quad_new();
void quad_free(quad_t* quad);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_MESH_H
