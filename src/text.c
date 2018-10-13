//
// Created by Thomas Lienbacher on 13.10.2018.
//

#include <stdlib.h>
#include <math.h>
#include "text.h"
#include "filehelper.h"

//TODO: scanning performance is super bad
font_t* font_newf(FILE *dataFile, FILE *bmpFile){
    font_t* font = calloc(1, sizeof(font_t));

    font->texture = texture_newf(bmpFile, GL_LINEAR, 1.0f);
    font->chars = calloc(256, sizeof(fontchar_t));

    char line[128];
    int c = 0;
    int cWidth;

    while(fgets(line, sizeof(line), dataFile)) {
        //metadata
        sscanf(line, "Cell Width,%d", &font->cellWidth);
        sscanf(line, "Cell Height,%d", &font->cellHeight);
        sscanf(line, "Start Char,%d", &font->startChar);
        sscanf(line, "Font Height,%d", &font->height);
        sscanf(line, "Global Width Offset,%d", &font->globalWidthOffset);//TODO: use this

        //chars
        if(sscanf(line, "Char %d Base Width,%d", &c, &cWidth) == 2) {
            if(c < font->startChar){
                printf("continue: %d\n", c);
                continue;
            }

            font->chars[c].c = (char)c;
            font->chars[c].width = cWidth;//global offset is added when building mesh

            float tw = (float)font->texture->width / (float) font->cellWidth;
            float th = (float)font->texture->width / (float) font->cellWidth;
            font->chars[c].tw = tw;
            font->chars[c].th = th;

            int row = (c-font->startChar) / (font->texture->width / font->cellWidth);
            int col = (c-font->startChar) % (font->texture->width / font->cellWidth);

            font->chars[c].tx = (float) col * tw;
            font->chars[c].ty = (float) row * th;

            //printf("%c - cs: %d, row: %d, col: %d\n", c, (c-font->startChar), row, col);
        }

    }

    /*printf("font: \n");
    printf("cell: %d x %d\n", font->cellWidth, font->cellHeight);
    printf("start: %d\n", font->startChar);
    printf("height: %d\n", font->height);
    printf("gwo: %d\n", font->globalWidthOffset);*/

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
