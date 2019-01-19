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

#define FONT_DEFAULT_SCALAR 0.1f

typedef struct _fontchar_s {
    float xadvance; //x advance
    float tx, ty, tw, th;//uv coords of char
} fontchar_t;

typedef struct _font_s {
    texture_t *texture;
    int startChar;
    float height;
    fontchar_t *chars;
    int cellHeight;
    int cellWidth;
} font_t;

typedef struct _text_s {
    GLuint vao;
    GLuint vbos[2];//vertices, texcoords
    GLuint numVertices;
    texture_t *texture;
    mat4x4 mat;
    float width, height;
} text_t;

font_t *font_newf(FILE *dataFile, FILE *pngFile, float scaler);

font_t *font_new(const char *dataFile, const char *bmpFile, float scaler);

void font_free(font_t *font);


text_t *text_new(font_t *font, const char *str);

void text_transform(text_t *text, vec2 pos, float scale);

void text_free(text_t *text);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_TEXT_H
