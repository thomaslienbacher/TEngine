//
// Created by Thomas Lienbacher on 20.01.2018.
//

/**
 * version: 1.1
 */

#ifndef TENGINE_CAMERA_H
#define TENGINE_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include "tengine_math.h"

typedef struct {
    mat4x4 projMat;
    mat4x4 viewMat;
    vec3 pos;
    float yaw, roll, pitch;
} camera_t;

camera_t* camera_new(float fov, float aspect, float near, float far);
void camera_view(camera_t* camera, vec3 pos, float pitch, float yaw, float roll);
void camera_free(camera_t* camera);

#ifdef __cplusplus
}
#endif

#endif //TENGINE_CAMERA_H
