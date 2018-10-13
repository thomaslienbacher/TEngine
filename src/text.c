//
// Created by Thomas Lienbacher on 13.10.2018.
//

#include <stdlib.h>
#include <math.h>
#include "text.h"
#include "filehelper.h"
#include "mesh.h"

//TODO: scanning performance is super bad
font_t* font_newf(FILE *dataFile, FILE *bmpFile){
    font_t* font = calloc(1, sizeof(font_t));

    font->texture = texture_newf(bmpFile, GL_LINEAR, 1.0f);
    font->chars = calloc(256, sizeof(fontchar_t));

    char line[128];
    int c = 0;
    int cWidth;

    //get header metadata
    for (int i = 0; i < 8; ++i) {

    }

    while(fgets(line, sizeof(line), dataFile)) {
        //metadata
        sscanf(line, "Cell Width,%d", &font->cellWidth);
        sscanf(line, "Cell Height,%d", &font->cellHeight);
        sscanf(line, "Start Char,%d", &font->startChar);
        sscanf(line, "Font Height,%d", &font->height);

        //chars
        if(sscanf(line, "Char %d Base Width,%d", &c, &cWidth) == 2) {
            if(c < font->startChar){
                continue;
            }

            font->chars[c].width = cWidth;//global offset is added when building mesh

            float th = 1.0f / ((float)font->texture->height / (float) font->cellHeight);
            font->chars[c].tw = 1.0f / ((float)font->texture->width / (float) cWidth);
            font->chars[c].th = th;

            int row = (c-font->startChar) / (font->texture->width / font->cellWidth);
            int col = (c-font->startChar) % (font->texture->width / font->cellWidth);

            font->chars[c].tx = (float) col * (1.0f / ((float)font->texture->width / (float) font->cellWidth));
            font->chars[c].ty = (float) row * th;

            //printf("%c - cs: %d, row: %d, col: %d\n", c, (c-font->startChar), row, col);
        }

    }

    font->xScale = 1.0f / (float)font->texture->width;
    font->yScale = 1.0f / (float)font->texture->height;

    /*printf("font: \n");
    printf("cell: %d x %d\n", font->cellWidth, font->cellHeight);
    printf("start: %d\n", font->startChar);
    printf("height: %d\n", font->height);*/

    return font;
}

font_t* font_new(const char *dataFile, const char *bmpFile){
    FILE *dFile = fadv_open(dataFile, "r");
    FILE *bFile = fadv_open(bmpFile, "rb");
    font_t *font = font_newf(dFile, bFile);
    fadv_close(dFile);
    fadv_close(bFile);

    return font;
}

void font_free(font_t* font){
    texture_free(font->texture);
    free(font->chars);
    free(font);
}

text_t *text_new(font_t* font, const char* str){
    text_t* text = calloc(1, sizeof(text_t));

    size_t len = strlen(str);
    unsigned int numVertices = len * 6;
    float *vertices = calloc(numVertices * 2, sizeof(float));
    float *texcoords = calloc(numVertices * 2, sizeof(float));

    //generate font data
    int pos = 0;
    int pos2 = 0;
    float curX = 0;
    float height = (float) font->height * font->yScale;

    for (int i = 0; i < len; ++i) {
        fontchar_t fc = font->chars[str[i]];
        float w = (float) fc.width * font->xScale;

        vertices[pos++] = curX;
        vertices[pos++] = 0;
        vertices[pos++] = curX + w;
        vertices[pos++] = 0;
        vertices[pos++] = curX + w;
        vertices[pos++] = height;

        vertices[pos++] = curX;
        vertices[pos++] = 0;
        vertices[pos++] = curX + w;
        vertices[pos++] = height;
        vertices[pos++] = curX;
        vertices[pos++] = height;

        texcoords[pos2++] = fc.tx;
        texcoords[pos2++] = fc.ty + fc.th;
        texcoords[pos2++] = fc.tx + fc.tw;
        texcoords[pos2++] = fc.ty + fc.th;
        texcoords[pos2++] = fc.tx + fc.tw;
        texcoords[pos2++] = fc.ty;

        texcoords[pos2++] = fc.tx;
        texcoords[pos2++] = fc.ty + fc.th;
        texcoords[pos2++] = fc.tx + fc.tw;
        texcoords[pos2++] = fc.ty;
        texcoords[pos2++] = fc.tx;
        texcoords[pos2++] = fc.ty;

        curX += w;
    }

    glGenVertexArrays(1, &text->vao);
    glBindVertexArray(text->vao);

    glGenBuffers(2, text->vbos);
    vao_add_vbo(text->vbos, 0, 2, vertices, numVertices * 2, POSITION_INDEX);
    vao_add_vbo(text->vbos, 1, 2, texcoords, numVertices * 2, TEXCOORD_INDEX);

    free(vertices);
    free(texcoords);

    text->numVertices = numVertices;
    text->texture = font->texture;
    text->width = curX;
    text->height = height;

    return text;
}

void text_transform(text_t *text, vec2 pos, float scale) {
    mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale, scale, 1);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], 0);

    mat4x4_identity(text->model);
    mat4x4_mul(text->model, scaleMat, translateMat);
}

void text_free(text_t *text){
    glDeleteVertexArrays(1, &text->vao);
    glDeleteBuffers(2, text->vbos);
    free(text);
}
