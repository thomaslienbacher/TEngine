//
// Created by Thomas Lienbacher on 20.01.2018.
//

#ifndef TENGINE_UTILS_H
#define TENGINE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

void _die(const char *msg, const char *file, const char *function, int line, const char *date, const char *time);

void _dief(const char *time, const char *file, const char *function, int line, const char *date, const char *format,
           ...);

#define die(msg) _die(msg, __FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__)
#define dief(msg, ...) _dief(__TIME__, __FILE__, __FUNCTION__, __LINE__, __DATE__, msg, __VA_ARGS__)

#ifdef DEBUG_BUILD
#define dprintf(format, ...) do { printf(format, __VA_ARGS__); } while(0)
#else
#define dprintf(format, ...)
#endif

#ifdef __cplusplus
}
#endif

#endif //TENGINE_UTILS_H
