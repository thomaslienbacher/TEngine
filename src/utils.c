//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.0
 */

#include <stdlib.h>
#include "utils.h"
#include "master.h"

void printmat(mat4x4 mat){
    for(int i = 0; i < 4; i++) {
        printf("col%d: %f %f %f %f\n", i, mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
    }
}

void model_mat_mat(mat4x4 mat, const vec3 pos, const vec3 rot, float scale){
    static mat4x4 scaleMat;
    mat4x4_identity(scaleMat);
    mat4x4_scale_aniso(scaleMat, scaleMat, scale, scale, scale);

    static mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate_Y(rotateMat, rotateMat, rot[1] * DEG_2_RAD);
    mat4x4_rotate_Z(rotateMat, rotateMat, rot[2] * DEG_2_RAD);
    mat4x4_rotate_X(rotateMat, rotateMat, rot[0] * DEG_2_RAD);

    static mat4x4 translateMat;
    mat4x4_translate(translateMat, pos[0], pos[1], pos[2]);

    mat4x4_identity(mat);
    mat4x4_mul(mat, mat, translateMat);
    mat4x4_mul(mat, mat, scaleMat);
    mat4x4_mul(mat, mat, rotateMat);
}

static void pre_die(FILE* errfile, const char* file, const char* function, int line){
    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    fprintf(errfile, "Vendor: %s\n", glGetString(GL_VENDOR));
    fprintf(errfile, "Renderer: %s\n", glGetString(GL_RENDERER));
    fprintf(errfile, "OpenGL: %d.%d\n\n", major, minor);

    fprintf(errfile, "Error: in %s at %s on line %d\n", file, function, line);
}

static void post_die(FILE* errfile, const char* date, const char* time){
    fprintf(errfile, "Build: %s %s\n\n", date, time);

#ifdef RELEASE_BUILD
    int numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    fprintf(errfile, "Num of extensions: %d\n", numExtensions);

    for(unsigned int i = 0; i < numExtensions; i++){
        fprintf(errfile, "   %s\n", glGetStringi(GL_EXTENSIONS, i));
    }
#endif

    fflush(errfile);
    fclose(errfile);
    exit(1);
}

void _die(const char* msg, const char* file, const char* function, int line, const char* date, const char* time){
    FILE* errfile = NULL;
#ifdef DEBUG_BUILD
    errfile = stderr;
#else
    errfile = fopen("log.txt", "w");
#endif

    pre_die(errfile, file, function, line);
    fprintf(errfile, "Msg: %s\n", msg);
    post_die(errfile, date, time);
}

void _dief(const char* time, const char* file, const char* function, int line, const char* date, const char* format, ...){
    FILE* errfile = NULL;
#ifdef DEBUG_BUILD
    errfile = stderr;
#else
    errfile = fopen("log.txt", "w");
#endif

    pre_die(errfile, file, function, line);

    fprintf(errfile, "Msg: ");
    va_list args;
    va_start(args, format);
    vfprintf(errfile, format, args);
    va_end(args);
    fprintf(errfile, "\n\n");
    post_die(errfile, date, time);
}
