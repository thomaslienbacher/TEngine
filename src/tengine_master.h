//
// Created by Thomas Lienbacher on 20.01.2018.
//

#ifndef TENGINE_TENGINE_MASTER_H
#define TENGINE_TENGINE_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define LODEPNG_NO_COMPILE_CPP

#include "lodepng.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef DEBUG_BUILD

extern int _debug_alloc_count;

static void *_debug_malloc(size_t _Size, const char *file, const char *function, int line) {
    _debug_alloc_count++;
    printf("malloc\t[%d]: %lld at %s in %s on line %d\n", _debug_alloc_count, _Size, file, function, line);
    return malloc(_Size);
}

static void *_debug_calloc(size_t _NumOfElements, size_t _SizeOfElements, const char *file, const char *function, int line) {
    _debug_alloc_count++;
    printf("calloc\t[%d]: %lld x %zu at %s in %s on line %d\n", _debug_alloc_count, _NumOfElements, _SizeOfElements,
           file, function, line);
    return calloc(_NumOfElements, _SizeOfElements);
}

static void *_debug_realloc(void *_Memory, size_t _NewSize, const char *file, const char *function, int line) {
    printf("realloc\t[%d]: %p to %zu at %s in %s on line %d\n", _debug_alloc_count, _Memory, _NewSize, file, function,
           line);
    return realloc(_Memory, _NewSize);
}

static void _debug_free(void *_Memory, const char *file, const char *function, int line) {
    _debug_alloc_count--;
    printf("free\t[%d]: %p at %s in %s on line %d\n", _debug_alloc_count, _Memory, file, function, line);
    free(_Memory);
}

static void te_check_allocations() {
    if (_debug_alloc_count) {
        printf("Error: %d allocations leaked!", _debug_alloc_count);
        exit(1);
    } else {
        printf("All allocations have been released!\n");
    }
}

#define te_malloc(_Size) _debug_malloc(_Size, __FILE__, __FUNCTION__, __LINE__)
#define te_calloc(_NumOfElements, _SizeOfElements) _debug_calloc(_NumOfElements, _SizeOfElements,__FILE__, __FUNCTION__, __LINE__)
#define te_realloc(_Memory, _NewSize) _debug_realloc(_Memory, _NewSize,__FILE__, __FUNCTION__, __LINE__)
#define te_free(_Memory) _debug_free(_Memory, __FILE__, __FUNCTION__, __LINE__)

#else

#define te_malloc(_Size) malloc(_Size)
#define te_calloc(_NumOfElements, _SizeOfElements) calloc(_NumOfElements, _SizeOfElements)
#define te_realloc(_Memory, _NewSize) realloc(_Memory, _NewSize)
#define te_free(_Memory) free(_Memory)

#endif

#ifdef __cplusplus
}
#endif

#endif //TENGINE_TENGINE_MASTER_H
