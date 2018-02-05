//
// Created by Thomas Lienbacher on 30.01.2018.
//

/**
 * version: 1.1
 */

#include <stdlib.h>
#include "filehelper.h"
#include "utils.h"

#define NULL_KILL(x) if(!(x)) die("File: file given was NULL")

FILE* fadv_open(const char* filename, const char* arg){
    FILE* f = fopen(filename, arg);
    if(!f) dief("File: file opened NULL: %s using %s", filename, arg);
    return f;
}

unsigned long fadv_length(FILE* f){
    NULL_KILL(f);
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    rewind(f);
    return len;
}

char* fadv_contents(FILE* f){
    NULL_KILL(f);
    rewind(f);
    unsigned long len = fadv_length(f);
    char* contents = malloc(len + 1);
    fread(contents, len, 1, f);
    contents[len] = 0;
    return contents;
}

void fadv_info(FILE* f, unsigned long* length, char** data){
    NULL_KILL(f);
    fseek(f, 0, SEEK_END);
    *length = (unsigned long)ftell(f);
    rewind(f);
    *data = malloc(*length + 1);
    fread(*data, *length, 1, f);
    (*data)[*length] = 0;
}

void fadv_close(FILE* f){
    NULL_KILL(f);
    fclose(f);
}