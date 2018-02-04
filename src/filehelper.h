//
// Created by Thomas Lienbacher on 30.01.2018.
//

/**
 * version: 1.0
 */

#ifndef TENGINE_FILEHELPER_H
#define TENGINE_FILEHELPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

//fadv = file advanced

FILE* fadv_open(const char* filename, const char* arg);
unsigned long fadv_length(FILE* f);
char* fadv_contents(FILE* f);
void fadv_info(FILE* f, unsigned long* length, char** data);
void fadv_close(FILE* f);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_FILEHELPER_H