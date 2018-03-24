//
// Created by Thomas Lienbacher on 20.02.2018.
//

#include <stdlib.h>
#include "vector.h"
#include "utils.h"

vector_t* vector_new(size_t capacity){
    vector_t* vec = calloc(1, sizeof(vector_t));
    vec->array = calloc(capacity, sizeof(void*));
    vec->size = capacity;

    return vec;
}

void vector_push(vector_t* vec, void* data){
    int nPos = -1;

    for (unsigned int i = 0; i < vec->size; ++i) {
        if(!vec->array[i]) {
            nPos = i;
            break;
        }
    }

    if(nPos == -1) {
        vec->size++;
        vec->array = realloc(vec->array, vec->size * sizeof(void*));
        vec->array[vec->size - 1] = data;
    }
    else {
        vec->array[nPos] = data;
    }
}

#define POS_CHECK(x) if((x) < 0 || 0 >= vec->size) dief("Vector: position out of bounds: %d", (x))

void* vector_remove(vector_t* vec, int pos) {
    POS_CHECK(pos);
    void* data = vec->array[pos];
    vec->array[pos] = NULL;
    return data;
}

void* vector_get(vector_t* vec, int pos) {
    POS_CHECK(pos);
    return vec->array[pos];
}

#undef POS_CHECK

void vector_trim(vector_t* vec){
    size_t newSize = vec->size;

    for (unsigned int i = 0; i < vec->size; ++i) {
        if(!vec->array[i]) newSize--;
    }

    void** newArray = calloc(newSize, sizeof(void*));
    int newI = 0;

    for (unsigned int i = 0; i < vec->size; ++i) {
        if(vec->array[i]) {
            newArray[newI] = vec->array[i];
            newI++;
        }
    }

    free(vec->array);
    vec->array = newArray;
    vec->size = newSize;
}

void vector_free(vector_t* vec) {
    free(vec->array);
    free(vec);
}