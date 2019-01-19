//
// Created by Thomas Lienbacher on 30.09.2018.
//

#ifndef TENGINE_FRUSTUM_H
#define TENGINE_FRUSTUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tengine_math.h"

typedef float frustum_plane_t[4];
typedef frustum_plane_t frustum_t[6];

void frustum_projview(frustum_t frustum, mat4x4 projview);

char frustum_ispoint(frustum_t frustum, vec3 p);

char frustum_issphere(frustum_t frustum, vec3 p, float radius);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_FRUSTUM_H
