
#include <stdio.h>
#include <windows.h>
#include "tengine_math.h"
#include "master.h"
#include "display.h"
#include "program.h"
#include "camera.h"
#include "mesh.h"
#include "render.h"
#include "light.h"
#include "filehelper.h"

void cam_control(camera_t* camera){
    const Uint8* kb = SDL_GetKeyboardState(NULL);

    static float x = 0;
    static float y = 0;
    static float z = 0;
    vec3 pos = {x, y, z};
    float a = 0.05f;
    if(kb[SDL_SCANCODE_W]) z -= a;
    if(kb[SDL_SCANCODE_S]) z += a;
    if(kb[SDL_SCANCODE_A]) x -= a;
    if(kb[SDL_SCANCODE_D]) x += a;
    if(kb[SDL_SCANCODE_Q]) y += a;
    if(kb[SDL_SCANCODE_E]) y -= a;
    //printf("pos: %f %f %f\n", x, y, z);

    static float xr = 0;
    static float yr = 0;
    static float zr = 0;
    vec3 rot = {xr, yr, zr};
    float r = 0.4f;
    if(kb[SDL_SCANCODE_I]) zr -= r;
    if(kb[SDL_SCANCODE_K]) zr += r;
    if(kb[SDL_SCANCODE_J]) xr -= r;
    if(kb[SDL_SCANCODE_L]) xr += r;
    if(kb[SDL_SCANCODE_U]) yr += r;
    if(kb[SDL_SCANCODE_O]) yr -= r;
    //printf("rot: %f %f %f\n", xr, yr, zr);

    camera_view(camera, pos, rot[0], rot[1], rot[2]);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int iCmdShow){
    vec3 tp = {23, 23, 11};
    float ts = 115.0f;
    vec3 tr2 = {0, 0, 0};

    mat4x4 test;
    model_mat_mat(test, tp, tr2, ts);
    vec3 dest;

    mat4x4_get_trans(dest, test);
    vec3_print(dest);
    _mat4x4_get_rotate(dest, test);
    vec3_print(dest);
    float dsts = 99;
    _mat4x4_get_scale(&dsts, test);
    printf("s: %f\n", dsts);


    //display
    const int WIDTH = 1200;
    const int HEIGHT = 500;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT);
    FILE* icon = fadv_open("data/icon.png", "rb");
    display_set_icon(display, icon);
    fadv_close(icon);

    //program
    FILE *vertex = fadv_open("data/vertex_shader.glsl", "r");
    FILE *fragment = fadv_open("data/fragment_shader.glsl", "r");
    program_t *program = program_new(vertex, fragment);
    fadv_close(vertex);
    fadv_close(fragment);
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);

#define MESH

    //mesh
#ifdef MESH
    FILE *obj = fadv_open("data/arena.obj", "r");
    mesh_t *mesh = mesh_newobj(obj);
    fadv_close(obj);
    FILE *obj2 = fadv_open("data/ico.obj", "r");
    mesh_t *mesh2 = mesh_newobj(obj2);
    fadv_close(obj2);

    //texture
    FILE *tex = fadv_open("data/arena.png", "rb");
    texture_t *texture = texture_new(tex, GL_LINEAR_MIPMAP_LINEAR, 4);
    fadv_close(tex);

    //model
    model_t *model = model_new(mesh, texture);
#endif

    //lightengine
#define w 2
    lightengine_t* lightengine = lightengine_new(program, w*w);
    for (int y = 0; y < w; ++y) {
        for (int x = 0; x < w; ++x) {
            vec3 pos = {x * 4, 3, y * 8};
            vec3 col = {1, 1, 1};
            float str = 10.1f;
            lightengine_set(lightengine, lightengine_get_id(lightengine), col, pos, str);
        }
    }

    while (display->running) {
        float delta;
        display_prepare(display, &delta);
        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f/delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        program_unistr_mat(program, "u_view", camera->viewMat);

        //render mesh
        if(kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        lightengine_upload(lightengine, program);

        //rendering
#ifdef MESH
        model->mesh = mesh;
        vec3 p = {0, 0, 0};
        float s = 1.0f;
        vec3 r = {0, 0, 0};
        model_mat(model, p, r, s);
        program_unistr_mat(program, "u_model", model->mat);
        program_use(program);
        render_model(model);

        static mat4x4 mats[w*w];
        model->mesh = mesh;

        for (int y = 0; y < w; ++y) {
            for (int x = 0; x < w; ++x) {
                vec3 posl = {x * 4, 0, y * 8};
                float scalel = 1.1f;
                vec3 tr = {x * 1.3f, x + y, y * 1.3f};
                model_mat_mat(mats[y * w + x], posl, tr, scalel);
            }
        }

        //render_instanced(model, program, w*w, mats);


        model->mesh = mesh2;
        for (int y = 0; y < w; ++y) {
            for (int x = 0; x < w; ++x) {
                vec3 posl = {x * 4, 3, y * 8};
                float scalel = 0.2f;
                vec3 tr = {x * 1.3f, x + y, y * 1.3f};
                model_mat_mat(mats[y * w + x], posl, tr, scalel);
            }
        }

        //render_instanced(model, program, w*w, mats);
#endif

        display_show(display);
    }

    lightengine_free(lightengine);
#ifdef MESH
    model_free(model);
    texture_free(texture);
    mesh_free(mesh);
#endif
    camera_free(camera);
    program_free(program);
    display_free(display);

    return 0;
}