//
// Created by Thomas Lienbacher on 20.01.2018.
//

#include <stdlib.h>
#include "camera.h"

camera_t *camera_new(float fov, float aspect, float near, float far) {
    camera_t *camera = calloc(1, sizeof(camera_t));

    mat4x4_perspective(camera->projMat, fov * DEG_2_RAD, aspect, near, far);
    mat4x4_identity(camera->viewMat);

    return camera;
}

void camera_view(camera_t *camera, vec3 pos, float pitch, float yaw) {
    mat4x4 rotateMat;
    mat4x4_identity(rotateMat);
    mat4x4_rotate(rotateMat, rotateMat, 1, 0, 0, pitch * DEG_2_RAD);
    mat4x4_rotate(rotateMat, rotateMat, 0, 1, 0, yaw * DEG_2_RAD);

    mat4x4 translateMat;
    mat4x4_translate(translateMat, -pos[0], -pos[1], -pos[2]);

    mat4x4_identity(camera->viewMat);
    mat4x4_mul(camera->viewMat, camera->viewMat, rotateMat);
    mat4x4_mul(camera->viewMat, camera->viewMat, translateMat);

    vec3_cpy(camera->pos, pos);
}

void camera_lookto(camera_t *camera, vec3 pos, vec3 direction) {
    vec3 center;
    vec3_add(center, pos, direction);
    mat4x4_look_at(camera->viewMat, pos, center, VEC3_UNITY);
}

void camera_free(camera_t *camera) {
    free(camera);
}