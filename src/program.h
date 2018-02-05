//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.1
 */

#ifndef TENGINE_program_H
#define TENGINE_program_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "master.h"
#include "linmath.h"

typedef struct {
    GLuint id;
    //uniform cache
} program_t;

program_t* program_new(FILE* vertexShd, FILE* fragmentShd);
void program_use(program_t* program);
int program_getunipos(program_t *program, const char *name);

void program_unistr_f(program_t *program, const char *name, float f);
void program_unistr_vec3(program_t *program, const char *name, vec3 v);
void program_unistr_vec4(program_t *program, const char *name, vec4 v);
void program_unistr_mat(program_t *program, const char *name, mat4x4 m);

void program_unipos_f(program_t *program, int loc, float f);
void program_unipos_vec3(program_t *program, int loc, vec3 v);
void program_unipos_vec4(program_t *program, int loc, vec4 v);
void program_unipos_mat(program_t *program, int loc, mat4x4 m);

void program_free(program_t* program);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_program_H
