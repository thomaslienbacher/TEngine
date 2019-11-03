//
// Created by Thomas Lienbacher on 20.01.2018.
//

#ifndef TENGINE_MASTER_H
#define TENGINE_MASTER_H

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

static int _debug_alloc_count = 0;

static void *_debug_malloc(size_t _Size, const char *file, const char *function, int line) {
    printf("malloc: %lld at %s in %s on line %d\n", _Size, file, function, line);
    _debug_alloc_count++;
    return malloc(_Size);
}

static void *_debug_calloc(size_t _NumOfElements, size_t _SizeOfElements, const char *file, const char *function, int line) {
    printf("calloc: %lld x %zu at %s in %s on line %d\n", _NumOfElements, _SizeOfElements, file, function, line);
    _debug_alloc_count++;
    return calloc(_NumOfElements, _SizeOfElements);
}

static void _debug_free(void *_Memory, const char *file, const char *function, int line) {
    printf("free: %p at %s in %s on line %d\n", _Memory, file, function, line);
    _debug_alloc_count--;
    free(_Memory);
}

static void _debug_check_allocations() {
    if (_debug_alloc_count) {
        printf("Error: %d allocations leaked!", _debug_alloc_count);
        exit(1);
    } else {
        printf("All allocations have been released!\n");
    }
}

#define malloc(_Size) _debug_malloc(_Size, __FILE__, __FUNCTION__, __LINE__)
#define calloc(_NumOfElements, _SizeOfElements) _debug_calloc(_NumOfElements, _SizeOfElements,__FILE__, __FUNCTION__, __LINE__)
#define free(_Memory) _debug_free(_Memory, __FILE__, __FUNCTION__, __LINE__)

#endif

#ifdef __cplusplus
}
#endif

#endif //TENGINE_MASTER_H
