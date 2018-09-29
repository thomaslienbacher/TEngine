//
// Created by Thomas Lienbacher on 30.01.2018.
//

#include <stdlib.h>
#include "filehelper.h"
#include "utils.h"

#define NULL_KILL(x) if(!(x)) die("File: file given was NULL")

FILE* fadv_open(const char* filename, const char* arg){
    FILE* f = fopen(filename, arg);
    if(!f) dief("File: file opened NULL: %s using %s", filename, arg);
    return f;
}

size_t fadv_length(FILE* f){
    NULL_KILL(f);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    if(len == -1) die("File: ftell returned -1");
    rewind(f);
    return (size_t)len;
}

char* fadv_contents(FILE* f){
    NULL_KILL(f);
    rewind(f);
    size_t len = fadv_length(f);
    char* contents = malloc(len + 1);
    fread(contents, len, 1, f);
    contents[len] = 0;
    return contents;
}

void fadv_info(FILE* f, size_t* length, char** data){
    NULL_KILL(f);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    if(len == -1) die("File: ftell returned -1");
    *length = (size_t) len;
    rewind(f);
    *data = malloc(*length + 1);
    fread(*data, *length, 1, f);
    (*data)[*length] = 0;
}

void fadv_close(FILE* f){
    NULL_KILL(f);
    fclose(f);
}