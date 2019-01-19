//
// Created by Thomas Lienbacher on 26.01.2018.
//

#include <stdlib.h>
#include "light.h"
#include "utils.h"

lightengine_t *lightengine_new(program_t *program, int numLights) {
    lightengine_t *lightengine = calloc(1, sizeof(lightengine_t));
    lightengine->numLights = numLights;
    lightengine->ids = calloc((size_t) numLights, sizeof(char));
    lightengine->lights = calloc((size_t) numLights, sizeof(light_t *));

    char name[32];

    for (int i = 0; i < numLights; ++i) {
        lightengine->lights[i] = calloc(1, sizeof(light_t));

        sprintf(name, "u_lightcolors[%d]", i);
        lightengine->lights[i]->colorLoc = program_getunipos(program, name);
        sprintf(name, "u_lightpositions[%d]", i);
        lightengine->lights[i]->posLoc = program_getunipos(program, name);
        sprintf(name, "u_lightstrengths[%d]", i);
        lightengine->lights[i]->strengthLoc = program_getunipos(program, name);

        if (lightengine->lights[i]->colorLoc < 0 || lightengine->lights[i]->posLoc < 0 ||
            lightengine->lights[i]->strengthLoc < 0) {
            dief("Light Engine: couldn't get uniform location: %d", i);
        }
    }

    return lightengine;
}

#define N_CHECK(x) if((x) < 0 || (x) >= lightengine->numLights) dief("Light Engine: light number out of bounds: %d", (x))

void lightengine_set(lightengine_t *lightengine, int n, vec3 color, vec3 pos, float strength) {
    N_CHECK(n);
    vec4_cpy(lightengine->lights[n]->color, color);
    vec3_cpy(lightengine->lights[n]->pos, pos);
    lightengine->lights[n]->strength = strength;
}

int lightengine_get_id(lightengine_t *lightengine) {
    for (int i = 0; i < lightengine->numLights; ++i) {
        if (!lightengine->ids[i]) {
            lightengine->ids[i] = 1;
            return i;
        }
    }

    return -1;
}

void lightengine_return_id(lightengine_t *lightengine, int id) {
    N_CHECK(id);
    lightengine->ids[id] = 0;
}

#undef N_CHECK

void lightengine_upload(lightengine_t *lightengine, program_t *program) {
    for (int i = 0; i < lightengine->numLights; ++i) {
        program_unipos_vec3(program, lightengine->lights[i]->colorLoc, lightengine->lights[i]->color);
        program_unipos_vec3(program, lightengine->lights[i]->posLoc, lightengine->lights[i]->pos);
        program_unipos_f(program, lightengine->lights[i]->strengthLoc, lightengine->lights[i]->strength);
    }
}

void lightengine_free(lightengine_t *lightengine) {
    for (int i = 0; i < lightengine->numLights; ++i) {
        free(lightengine->lights[i]);
    }

    free(lightengine->lights);
    free(lightengine->ids);
    free(lightengine);
}