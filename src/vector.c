//
// Created by Thomas Lienbacher on 20.02.2018.
//

#include <stdlib.h>
#include "vector.h"

vector* vector_new(int capacity){
    vector* vec = calloc(1, sizeof(vector));
    vec->array = calloc((size_t)capacity, sizeof(void*));
    vec->size = capacity;

    return vec;
}

void vector_push(vector* vec, void* data){
    int nPos = -1;

    for (int i = 0; i < vec->size; ++i) {
        if(!vec->array[i]) {
            nPos = i;
            break;
        }
    }

    if(nPos == -1) {

    }
    else {
        
    }
}

void vector_remove(vector* vec, int pos){

}

void* vector_get(vector* vec){

}

void vector_trim(vector* vec){

}

void vector_free(vector* vec) {

}