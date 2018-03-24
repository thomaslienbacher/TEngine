//
// Created by Thomas Lienbacher on 20.01.2018.
//

#include <stdlib.h>
#include "utils.h"
#include "master.h"

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

    for(int i = 0; i < numExtensions; i++){
        fprintf(errfile, "   %s\n", glGetStringi(GL_EXTENSIONS, (GLuint)i));
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
