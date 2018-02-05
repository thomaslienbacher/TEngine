//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.2
 */

#include <stdlib.h>
#include "program.h"
#include "utils.h"
#include "filehelper.h"

program_t* program_new(FILE* vertexShd, FILE* fragmentShd){
    program_t* program = calloc(1, sizeof(program_t));

    program->id = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //vertex shader
    unsigned long vertexLen = 0;
    char* vertexSrc = NULL;
    fadv_info(vertexShd, &vertexLen, &vertexSrc);
    glShaderSource(vertex, 1, (const char**)&vertexSrc, (const GLint*)&vertexLen);
    glCompileShader(vertex);
    free(vertexSrc);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &maxLength);

        char infoLog[maxLength];
        glGetShaderInfoLog(vertex, maxLength, &maxLength, infoLog);
        infoLog[maxLength-1] = 0;
        dief("Vertex Shader: %s", infoLog);
    }

    //fragment shader
    unsigned long fragmentLen = 0;
    char* fragmentSrc = NULL;
    fadv_info(fragmentShd, &fragmentLen, &fragmentSrc);
    glShaderSource(fragment, 1, (const char**)&fragmentSrc, (const GLint*)&fragmentLen);
    glCompileShader(fragment);
    free(fragmentSrc);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);

        char infoLog[maxLength];
        glGetShaderInfoLog(fragment, maxLength, &maxLength, infoLog);
        infoLog[maxLength-1] = 0;
        dief("Fragment Shader: %s", infoLog);
    }

    //link
    glAttachShader(program->id, vertex);
    glAttachShader(program->id, fragment);

    glLinkProgram(program->id);

    GLint isLinked = 0;
    glGetProgramiv(program->id, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, &maxLength);

        char infoLog[maxLength];
        glGetProgramInfoLog(program->id, maxLength, &maxLength, infoLog);
        infoLog[maxLength-1] = 0;
        dief("Program Link: %s", infoLog);
    }

    glDetachShader(program->id, vertex);
    glDetachShader(program->id, fragment);

    return program;
}

static GLuint used = 0;

void program_use(program_t* program){
    if(program == NULL) {
        glUseProgram(0);
        used = 0;
    }
    else if(used != program->id) {
        glUseProgram(program->id);
        used = program->id;
    }
}

int program_getunipos(program_t *program, const char *name){
    program_use(program);
    return glGetUniformLocation(program->id, name);
}


void program_unistr_f(program_t *program, const char *name, float f){
    program_use(program);
    GLint loc = glGetUniformLocation(program->id, name);
    glUniform1f(loc, f);
}

void program_unistr_vec3(program_t *program, const char *name, vec3 v){
    program_use(program);
    GLint loc = glGetUniformLocation(program->id, name);
    glUniform3fv(loc, 1, v);
}

void program_unistr_vec4(program_t *program, const char *name, vec4 v){
    program_use(program);
    GLint loc = glGetUniformLocation(program->id, name);
    glUniform4fv(loc, 1, v);
}

void program_unistr_mat(program_t *program, const char *name, mat4x4 m){
    program_use(program);
    GLint loc = glGetUniformLocation(program->id, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, m[0]);
}


void program_unipos_f(program_t *program, int loc, float f){
    program_use(program);
    glUniform1f(loc, f);
}

void program_unipos_vec3(program_t *program, int loc, vec3 v){
    program_use(program);
    glUniform3fv(loc, 1, v);
}

void program_unipos_vec4(program_t *program, int loc, vec4 v){
    program_use(program);
    glUniform4fv(loc, 1, v);
}

void program_unipos_mat(program_t *program, int loc, mat4x4 m){
    program_use(program);
    glUniformMatrix4fv(loc, 1, GL_FALSE, m[0]);
}


void program_free(program_t* program){
    program_use(NULL);
    glDeleteProgram(program->id);
}
