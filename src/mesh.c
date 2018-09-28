//
// Created by Thomas Lienbacher on 20.01.2018.
//

#include "mesh.h"
#include "master.h"
#include "utils.h"
#include "filehelper.h"
#include "tinyobj_loader_c.h"

mesh_t* mesh_newobjf(FILE *objFile){
    //obj parsing
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t* materials = NULL;
    size_t num_materials;

    char* temp = NULL;
    unsigned long data_len = 0;
    fadv_info(objFile, &data_len, &temp);
    char* data = malloc(data_len + 3);
    strcpy(data, temp);
    strcat(data, "\n\n");   //If I dont add 2 x \n to the data the last face doesnt get parsed
                            //I don't know why the this happens, maybe my fadv_ functions are faulty
                            //just leave the the lines as they are it works and if I change anything it will crash
    free(temp);

    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
    int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, &num_materials, data, data_len+2, flags);
    free(data);

    if (ret != TINYOBJ_SUCCESS) {
        die("Error: obj not loaded");
    }

    //single index obj
    unsigned int* indices = malloc(attrib.num_faces * sizeof(unsigned int));
    float* vertices = malloc(attrib.num_faces * sizeof(float) * 3);
    float* texcoords = malloc(attrib.num_faces * sizeof(float) * 2);
    float* normals = malloc(attrib.num_faces * sizeof(float) * 3);

    unsigned int indicesIndex;
    unsigned int vertexIndex = 0;

    for (indicesIndex = 0; indicesIndex < attrib.num_faces; ++indicesIndex) {
        char inarray = 0;
        unsigned int pos = 0;

        for(unsigned int i = 0; i < vertexIndex; i++) {
            if (vertices[3*i] == attrib.vertices[3*attrib.faces[indicesIndex].v_idx] &&
                vertices[3*i+1] == attrib.vertices[3*attrib.faces[indicesIndex].v_idx+1] &&
                vertices[3*i+2] == attrib.vertices[3*attrib.faces[indicesIndex].v_idx+2] &&

                texcoords[2*i] == attrib.texcoords[2*attrib.faces[indicesIndex].vt_idx] &&
                texcoords[2*i+1] == attrib.texcoords[2*attrib.faces[indicesIndex].vt_idx+1] &&

                normals[3*i] == attrib.normals[3*attrib.faces[indicesIndex].vn_idx] &&
                normals[3*i+1] == attrib.normals[3*attrib.faces[indicesIndex].vn_idx+1] &&
                normals[3*i+2] == attrib.normals[3*attrib.faces[indicesIndex].vn_idx+2]) {

                inarray = 1;
                pos = i;
                break;
            }
        }

        //check if I already put this into the buffers, if yes put the index number in to the index buffer
        if(inarray){
            indices[indicesIndex] = pos;
        }
        //if not put it into the buffer
        else{
            vertices[3*vertexIndex] = attrib.vertices[3*attrib.faces[indicesIndex].v_idx];
            vertices[3*vertexIndex+1] = attrib.vertices[3*attrib.faces[indicesIndex].v_idx+1];
            vertices[3*vertexIndex+2] = attrib.vertices[3*attrib.faces[indicesIndex].v_idx+2];

            texcoords[2*vertexIndex] = attrib.texcoords[2*attrib.faces[indicesIndex].vt_idx];
            texcoords[2*vertexIndex+1] = 1.0f - attrib.texcoords[2*attrib.faces[indicesIndex].vt_idx+1];

            normals[3*vertexIndex] = attrib.normals[3*attrib.faces[indicesIndex].vn_idx];
            normals[3*vertexIndex+1] = attrib.normals[3*attrib.faces[indicesIndex].vn_idx+1];
            normals[3*vertexIndex+2] = attrib.normals[3*attrib.faces[indicesIndex].vn_idx+2];

            indices[indicesIndex] = vertexIndex;
            vertexIndex++;
        }
    }

    mesh_t* mesh = mesh_newdata(attrib.num_faces, indices, vertexIndex, vertices, texcoords, normals);

    //cleanup
    tinyobj_attrib_free(&attrib);
    tinyobj_shapes_free(shapes, num_shapes);
    tinyobj_materials_free(materials, num_materials);
    free(vertices);
    free(texcoords);
    free(normals);
    free(indices);

    return mesh;
}

mesh_t* mesh_newobj(const char *objFile) {
    FILE *obj = fadv_open(objFile, "r");
    mesh_t *mesh = mesh_newobjf(obj);
    fadv_close(obj);

    return mesh;
}

static void mesh_add_vbo(mesh_t* mesh, int vbo, int size, float* data, unsigned int len, unsigned int index){
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[vbo]);
    glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

mesh_t* mesh_newdata(unsigned int numIndices, unsigned int* indices, unsigned int numVertices,
                     float* vertices, float* texcoords, float* normals){
    mesh_t* mesh = calloc(1, sizeof(mesh_t));

    mesh->numElements = numIndices;

    //opengl upload
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    glGenBuffers(4, mesh->vbos);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbos[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    mesh_add_vbo(mesh, 1, 3, vertices, numVertices*3, POSITION_INDEX);
    mesh_add_vbo(mesh, 2, 2, texcoords, numVertices*2, TEXCOORD_INDEX);
    mesh_add_vbo(mesh, 3, 3, normals, numVertices*3, NORMAL_INDEX);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return mesh;
}

static unsigned int bound = 0;

static const float QUAD_VERTICES[] = {-1, -1, 1, -1, 1, 1,
                                      -1, -1, 1, 1, -1, 1};

static const float QUAD_UVS[] = {0, 1, 1, 1, 1, 0,
                                 0, 1, 1, 0, 0, 0};

void mesh_bind(mesh_t* mesh){
    if(mesh == NULL){
        if(bound) {
            glBindVertexArray(0);
            bound = 0;
        }
    }
    else if(mesh->vao != bound) {
        glBindVertexArray(mesh->vao);
        bound = mesh->vao;
    }
}

void mesh_free(mesh_t* mesh){
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(4, mesh->vbos);
    free(mesh);
}

quad_t* quad_new() {
    quad_t* quad = calloc(1, sizeof(quad_t));

    glGenVertexArrays(1, &quad->vao);
    glBindVertexArray(quad->vao);

    glGenBuffers(2, quad->vbo);
    mesh_add_vbo((mesh_t*) quad, 0, 2, QUAD_VERTICES, QUAD_SIZE*2, POSITION_INDEX);
    mesh_add_vbo((mesh_t*) quad, 1, 2, QUAD_UVS, QUAD_SIZE*2, TEXCOORD_INDEX);

    return quad;
}

void quad_free(quad_t* quad) {
    glDeleteVertexArrays(1, &quad->vao);
    glDeleteBuffers(2, quad->vbo);
    free(quad);
}