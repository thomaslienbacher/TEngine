//
// Created by Thomas Lienbacher on 20.02.2018.
//

#ifndef TENGINE_VECTOR_H
#define TENGINE_VECTOR_H

typedef struct {
    void** array;
    int size;
} vector;

vector* vector_new(int capacity);
void vector_push(vector* vec, void* data);
void vector_remove(vector* vec, int pos);
void* vector_get(vector* vec);
void vector_trim(vector* vec);
void vector_free(vector* vec);

#endif //TENGINE_VECTOR_H
