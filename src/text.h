//
// Created by Thomas Lienbacher on 13.10.2018.
//

#ifndef TENGINE_TEXT_H
#define TENGINE_TEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "master.h"
#include "texture.h"
#include "tengine_math.h"

typedef struct {
    int width;
    float tx, ty, tw, th;//uv coords of char
} fontchar_t;

//TODO: store everything as floats in opengl viewspace coords
typedef struct _font_s {
    texture_t *texture;
    int startChar;
    int height;
    fontchar_t *chars;
    int cellHeight;
    int cellWidth;
    float xScale, yScale;//int data to opengl data
} font_t;

font_t *font_newf(FILE *dataFile, FILE *bmpFile);
font_t *font_new(const char *dataFile, const char *bmpFile);
void font_free(font_t *font);


typedef struct _text_s {
    GLuint vao;
    GLuint vbos[2];//vertices, texcoords
    GLuint numVertices;
    texture_t *texture;
    mat4x4 model;
    float width, height;
} text_t;

text_t *text_new(font_t* font, const char* str);
void text_transform(text_t *text, vec2 pos, float scale);
void text_free(text_t *text);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_TEXT_H
