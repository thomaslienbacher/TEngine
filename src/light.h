//
// Created by Thomas Lienbacher on 26.01.2018.
//

#ifndef TENGINE_LIGHT_H
#define TENGINE_LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include "tengine_math.h"
#include "program.h"

typedef struct _light_s {
    vec3 color;
    vec3 pos;
    float strength; //if set to 0 light will not be calculated
    int colorLoc;
    int posLoc;
    int strengthLoc;
} light_t;

typedef struct _lightengine_s {
    int numLights;
    light_t **lights;
    unsigned char *ids;//0 = not used, 1 = used
} lightengine_t;

lightengine_t *lightengine_new(program_t *program, int numLights);

void lightengine_set(lightengine_t *lightengine, int n, vec3 color, vec3 pos, float strength);

int lightengine_get_id(lightengine_t *lightengine); // if no ids are left -1 is returned

void lightengine_return_id(lightengine_t *lightengine, int id);

void lightengine_upload(lightengine_t *lightengine, program_t *program);

void lightengine_free(lightengine_t *lightengine);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_LIGHT_H
