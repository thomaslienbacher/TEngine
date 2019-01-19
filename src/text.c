//
// Created by Thomas Lienbacher on 13.10.2018.
//

#include <stdlib.h>
#include <math.h>
#include "text.h"
#include "filehelper.h"
#include "mesh.h"
#include "utils.h"

font_t *font_newf(FILE *dataFile, FILE *pngFile, float scaler) {
    font_t *font = calloc(1, sizeof(font_t));

    font->texture = texture_newf(pngFile, GL_LINEAR, 1.0f);
    font->chars = calloc(256, sizeof(fontchar_t));
    float xScale = 1.0f / (float) font->texture->width;
    float yScale = 1.0f / (float) font->texture->height;

    char line[128];
    int c = 0;
    int charWidth;
    int fontHeight;

    //get header metadata
    for (int i = 0; i < 8; ++i) {
        if (!fgets(line, sizeof(line), dataFile)) die("Text: error reading file!");

        sscanf(line, "Cell Width,%d", &font->cellWidth);
        sscanf(line, "Cell Height,%d", &font->cellHeight);
        sscanf(line, "Start Char,%d", &font->startChar);
        sscanf(line, "Font Height,%d", &fontHeight);
    }

    float scale = 1.0f / (float) fontHeight * scaler;
    font->height = (float) font->cellHeight * scale;

    while (fgets(line, sizeof(line), dataFile)) {
        if (sscanf(line, "Char %d Base Width,%d", &c, &charWidth) == 2) {
            if (c < font->startChar) {
                continue;
            }

            int charNum = (c - font->startChar);
            font->chars[c].xadvance = (float) charWidth * scale;

            float th = (float) font->cellHeight * yScale;
            font->chars[c].tw = (float) charWidth * xScale;
            font->chars[c].th = th;

            int row = charNum / (font->texture->width / font->cellWidth);
            int col = charNum % (font->texture->width / font->cellWidth);

            font->chars[c].tx = (float) col * (float) font->cellWidth * xScale;
            font->chars[c].ty = (float) row * th;

            if (c == 255) break;
        }

    }

    return font;
}

font_t *font_new(const char *dataFile, const char *bmpFile, float scaler) {
    FILE *dFile = fadv_open(dataFile, "r");
    FILE *bFile = fadv_open(bmpFile, "rb");
    font_t *font = font_newf(dFile, bFile, scaler);
    fadv_close(dFile);
    fadv_close(bFile);

    return font;
}

void font_free(font_t *font) {
    texture_free(font->texture);
    free(font->chars);
    free(font);
}

text_t *text_new(font_t *font, const char *str) {
    text_t *text = calloc(1, sizeof(text_t));

    size_t len = strlen(str);
    size_t numVertices = len * 6;
    float *vertices = calloc(numVertices * 2, sizeof(float));
    float *texcoords = calloc(numVertices * 2, sizeof(float));

    //generate font data
    int pa = 0;
    int pb = 0;
    float curX = 0;

    for (unsigned int i = 0; i < len; ++i) {
        fontchar_t fc = font->chars[str[i]];

        vertices[pa++] = curX;
        vertices[pa++] = 0;
        vertices[pa++] = curX + fc.xadvance;
        vertices[pa++] = 0;
        vertices[pa++] = curX + fc.xadvance;
        vertices[pa++] = font->height;

        vertices[pa++] = curX;
        vertices[pa++] = 0;
        vertices[pa++] = curX + fc.xadvance;
        vertices[pa++] = font->height;
        vertices[pa++] = curX;
        vertices[pa++] = font->height;

        texcoords[pb++] = fc.tx;
        texcoords[pb++] = fc.ty + fc.th;
        texcoords[pb++] = fc.tx + fc.tw;
        texcoords[pb++] = fc.ty + fc.th;
        texcoords[pb++] = fc.tx + fc.tw;
        texcoords[pb++] = fc.ty;

        texcoords[pb++] = fc.tx;
        texcoords[pb++] = fc.ty + fc.th;
        texcoords[pb++] = fc.tx + fc.tw;
        texcoords[pb++] = fc.ty;
        texcoords[pb++] = fc.tx;
        texcoords[pb++] = fc.ty;

        curX += fc.xadvance;
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
    text->height = font->height;

    mat4x4_identity(text->mat);

    return text;
}

void text_transform(text_t *text, vec2 pos, float scale) {
    mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale, scale, 1);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], 0);

    mat4x4_identity(text->mat);
    mat4x4_mul(text->mat, translateMat, scaleMat);
}

void text_free(text_t *text) {
    glDeleteVertexArrays(1, &text->vao);
    glDeleteBuffers(2, text->vbos);
    free(text);
}
