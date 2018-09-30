//
// Created by Thomas Lienbacher on 20.02.2018.
//

#ifndef TENGINE_VECTOR_H
#define TENGINE_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct _vector_s {
    void** array;
    size_t size;
} vector_t;

vector_t* vector_new(size_t capacity);
void vector_push(vector_t* vec, void* data);
void* vector_remove(vector_t* vec, int pos);
void* vector_get(vector_t* vec, int pos);
void vector_trim(vector_t* vec);
void vector_free(vector_t* vec);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_VECTOR_H
