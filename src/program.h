//
// Created by Thomas Lienbacher on 20.01.2018.
//

#ifndef TENGINE_program_H
#define TENGINE_program_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "master.h"
#include "tengine_math.h"

typedef struct _program_s {
    GLuint id;
    //uniform cache
} program_t;

program_t* program_news(const char *vertexSrc, const char *fragmentSrc);
program_t* program_newf(FILE *vertexShd, FILE *fragmentShd);
program_t* program_new(const char *vertexFile, const char *fragmenFile);
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
