#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "tengine_math.h"
#include "master.h"
#include "display.h"
#include "program.h"
#include "camera.h"
#include "mesh.h"
#include "render.h"
#include "light.h"
#include "vector.h"
#include "frustum.h"

#ifdef  __REMOVE_FROM_COMPILATION__

//deprecated
void test_render() {
    //display
    const int WIDTH = 1200;
    const int HEIGHT = 500;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, 0);
    display_set_icon(display, "data/icon.png");

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);

#define MESH

    //mesh
#ifdef MESH
    mesh_t *mesh = mesh_newobj("data/arena.obj");
    mesh_t *mesh2 = mesh_newobj("data/ico.obj");

    //texture
    texture_t *texture = texture_new("data/arena.png", GL_LINEAR_MIPMAP_LINEAR, 4);

    //model
    model_t *model = model_new(mesh, texture);
#endif

    //lightengine
#define NL 2
    lightengine_t *lightengine = lightengine_new(program, NL * NL);
    for (int y = 0; y < NL; ++y) {
        for (int x = 0; x < NL; ++x) {
            vec3 pos = {x * 3, 3, y * 3};
            vec3 col = {1, 1, 1};
            float str = 1.1f;
            lightengine_set(lightengine, lightengine_get_id(lightengine), col, pos, str);
        }
    }

    while (display->running) {
        float delta;
        display_prepare(display, &delta, 0);
        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        program_unistr_mat(program, "u_view", camera->viewMat);

        //render mesh
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

        static mat4x4 mats[NL * NL];
        model->mesh = mesh;

        for (int y = 0; y < NL; ++y) {
            for (int x = 0; x < NL; ++x) {
                vec3 posl = {x * 4, 0, y * 8};
                float scalel = 1.1f;
                vec3 tr = {x * 1.3f, x + y, y * 1.3f};
                model_mat_mat(mats[y * NL + x], posl, tr, scalel);
            }
        }

        //render_instanced_dyn(model, program, w*w, mats);


        model->mesh = mesh2;
        for (int y = 0; y < NL; ++y) {
            for (int x = 0; x < NL; ++x) {
                vec3 posl = {x * 3, 3, y * 3};
                float scalel = 0.2f;
                vec3 tr = {x * 1.3f, x + y, y * 1.3f};
                model_mat_mat(mats[y * NL + x], posl, tr, scalel);
            }
        }

        render_instanced_dyn(model, program, NL * NL, mats);
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
}

void print_vec(vector_t *vec) {
    for (int j = 0; j < vec->size; ++j) {
        int *d = ((int *) vector_get(vec, j));
        printf("%d -> %p -> ", j, d);
        if (d) printf("%d\n", *d);
        else printf("\n");
    }
}

void test_vector() {
    vector_t *vec = vector_new(10);

    for (int i = 0; i < 200; ++i) {
        int *d = malloc(sizeof(int));
        *d = i * i;
        vector_push(vec, d);
        printf("%d -> size: %d\n", i, vec->size);
    }

    print_vec(vec);

    free(vector_remove(vec, 10));
    free(vector_remove(vec, 11));
    free(vector_remove(vec, 12));

    print_vec(vec);
    vector_trim(vec);
    print_vec(vec);

    for (int j = 0; j < vec->size; ++j) {
        free(vector_remove(vec, j));
    }

    print_vec(vec);
    vector_free(vec);
}

void print_display_modes() {
    static int display_in_use = 0; /* Only using first display */

    int i, display_mode_count;
    SDL_DisplayMode mode;
    Uint32 f;

    SDL_Log("SDL_GetNumVideoDisplays(): %i", SDL_GetNumVideoDisplays());

    display_mode_count = SDL_GetNumDisplayModes(display_in_use);
    if (display_mode_count < 1) {
        SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
        return;
    }
    SDL_Log("SDL_GetNumDisplayModes: %i", display_mode_count);

    for (i = 0; i < display_mode_count; ++i) {
        if (SDL_GetDisplayMode(display_in_use, i, &mode) != 0) {
            SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
            return;
        }
        f = mode.format;

        SDL_Log("Mode %i\tbpp %i\t%s\t%i x %i", i,
                SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), mode.w, mode.h);
    }
}

//deprecated
void test_instanced_model() {
    //display
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, 0);

    print_display_modes();

    display_set_icon(display, "data/icon.png");
    SDL_SetWindowFullscreen(display->window, SDL_WINDOW_FULLSCREEN);

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);

    //model
    mesh_t *mesh = mesh_newobj("data/ico.obj");
    mesh_t *mesh2 = mesh_newobj("data/gun.obj");
    mesh_t *mesh3 = mesh_newobj("data/arena.obj");
    texture_t *texture = texture_new("data/arena.png", GL_NEAREST, 1);
    texture_t *texture2 = texture_new("data/icon.png", GL_NEAREST, 1);
    texture_t *texture3 = texture_new("data/gun_low.png", GL_NEAREST, 1);
    model_t *model = model_new(mesh, texture);

#define S 14

    static mat4x4 mats[S * S];

    while (display->running) {
        float delta;
        display_prepare(display, &delta, 0);
        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);
        dprintf("%s\n", title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        program_unistr_mat(program, "u_view", camera->viewMat);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        for (float i = 1.0f; i < 6.0f; i += 0.4f) {
            model->texture = texture;
            model->mesh = mesh;
            {
                for (int x = 0; x < S; ++x) {
                    for (int y = 0; y < S; ++y) {
                        vec3 _pos = {x * 2, -i, y * 2};
                        vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f,
                                     360.0f - (SDL_GetTicks() / 300.f)};
                        float _s = 0.5f;
                        model_mat_mat(mats[y * S + x], _pos, _rot, _s);
                    }
                }

                render_instanced_dyn(model, program, S * S, mats);
            }

            model->texture = texture2;
            model->mesh = mesh2;
            {
                for (int x = 0; x < S; ++x) {
                    for (int y = 0; y < S; ++y) {
                        vec3 _pos = {x * 2, 3 * i, y * 2};
                        vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f,
                                     360.0f - (SDL_GetTicks() / 300.f)};
                        float _s = 0.2f;
                        model_mat_mat(mats[y * S + x], _pos, _rot, _s);
                    }
                }

                render_instanced_dyn(model, program, S * S, mats);
            }

            model->texture = texture3;
            model->mesh = mesh3;
            {
                for (int x = 0; x < S; ++x) {
                    for (int y = 0; y < S; ++y) {
                        vec3 _pos = {x * 2, 6 * i, y * 2};
                        vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f,
                                     360.0f - (SDL_GetTicks() / 300.f)};
                        float _s = 0.05f;
                        model_mat_mat(mats[y * S + x], _pos, _rot, _s);
                    }
                }

                render_instanced_dyn(model, program, S * S, mats);
            }
        }

        display_show(display);
    }


    model_free(model);
    texture_free(texture);
    texture_free(texture2);
    texture_free(texture3);
    mesh_free(mesh);
    mesh_free(mesh2);
    mesh_free(mesh3);

    camera_free(camera);
    program_free(program);
    display_free(display);
}

//deprecated
void test_instanced_model_new() {
    //display
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, 0);

    print_display_modes();

    display_set_icon(display, "data/icon.png");
    SDL_SetWindowFullscreen(display->window, SDL_WINDOW_FULLSCREEN);

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);

    //model
    mesh_t *mesh = mesh_newobj("data/ico.obj");
    mesh_t *mesh2 = mesh_newobj("data/gun.obj");
    mesh_t *mesh3 = mesh_newobj("data/arena.obj");
    texture_t *texture = texture_new("data/arena.png", GL_NEAREST, 1);
    texture_t *texture2 = texture_new("data/icon.png", GL_NEAREST, 1);
    texture_t *texture3 = texture_new("data/gun_low.png", GL_NEAREST, 1);
    inst_model_t *model = inst_model_new(mesh, texture, S * S);
    inst_model_t *model2 = inst_model_new(mesh2, texture2, S * S);
    inst_model_t *model3 = inst_model_new(mesh3, texture3, S * S);

    static mat4x4 mats[S * S];

    while (display->running) {
        float delta;
        display_prepare(display, &delta, 0);
        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);
        dprintf("%s\n", title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        program_unistr_mat(program, "u_view", camera->viewMat);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        for (float i = 1.0f; i < 6.0f; i += 0.4f) {
            {
                if (clock() < 1500)
                    for (int x = 0; x < S; ++x) {
                        for (int y = 0; y < S; ++y) {
                            vec3 _pos = {x * 2, -i, y * 2};
                            vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f,
                                         360.0f - (SDL_GetTicks() / 300.f)};
                            float _s = 0.5f;
                            model_mat_mat(model->mats[y * S + x], _pos, _rot, _s);
                        }
                    }

                if (clock() < 1500)inst_model_update(model);
                render_inst_model(model, program);
            }

            {
                if (clock() < 1500)
                    for (int x = 0; x < S; ++x) {
                        for (int y = 0; y < S; ++y) {
                            vec3 _pos = {x * 2, 3 * i, y * 2};
                            vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f,
                                         360.0f - (SDL_GetTicks() / 300.f)};
                            float _s = 0.2f;
                            model_mat_mat(model2->mats[y * S + x], _pos, _rot, _s);
                        }
                    }

                if (clock() < 1500)inst_model_update(model2);
                render_inst_model(model2, program);
            }

            {

                if (clock() < 1500)
                    for (int x = 0; x < S; ++x) {
                        for (int y = 0; y < S; ++y) {
                            vec3 _pos = {x * 2, 6 * i, y * 2};
                            vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f,
                                         360.0f - (SDL_GetTicks() / 300.f)};
                            float _s = 0.05f;
                            model_mat_mat(model3->mats[y * S + x], _pos, _rot, _s);
                        }
                    }

                if (clock() < 1500)inst_model_update(model3);
                render_inst_model(model3, program);
            }
        }

        display_show(display);
    }


    inst_model_free(model);
    inst_model_free(model2);
    inst_model_free(model3);
    texture_free(texture);
    texture_free(texture2);
    texture_free(texture3);
    mesh_free(mesh);
    mesh_free(mesh2);
    mesh_free(mesh3);

    camera_free(camera);
    program_free(program);
    display_free(display);
}

void print_fb() {
    GLint drawFboId = 0, readFboId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

    fflush(stdout);
    fflush(stderr);

    dprintf("fb: draw: %d read: %d\n", drawFboId, readFboId);
}

//deprecated
void test_screen() {
    //display
    const int WIDTH = 640;
    const int HEIGHT = 480;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, 0);
    display_set_icon(display, "data/icon.png");
    print_display_modes();

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);

    //inst_model
    mesh_t *mesh = mesh_newobj("data/ico.obj");
    mesh_t *mesh2 = mesh_newobj("data/plane.obj");
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    inst_model_t *inst_model = inst_model_new(mesh, texture, S * S);
    model_t *model = model_new(mesh2, NULL);

    //framebuffer
    framebuffer_t *framebuffer = framebuffer_new(WIDTH, HEIGHT);
    model->texture = framebuffer->texture;

    while (display->running) {
        float delta;
        display_prepare(display, &delta, 0);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        program_unistr_mat(program, "u_view", camera->viewMat);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        framebuffer_bind(framebuffer);
        framebuffer_clear(framebuffer);

        //render
        for (int x = 0; x < S; ++x) {
            for (int y = 0; y < S; ++y) {
                vec3 _pos = {x * 2, 0, y * 2};
                vec3 _rot = {SDL_GetTicks() / 300.f * x, SDL_GetTicks() / 100.0f, 360.0f - (SDL_GetTicks() / 300.f)};
                float _s = 0.3f;
                model_mat_mat(inst_model->mats[y * S + x], _pos, _rot, _s);
            }
        }

        vec3_print(camera->pos);

        inst_model_update(inst_model);
        render_inst_model(inst_model, program);

        framebuffer_bind(NULL);

        model_mat(model, VEC3_ZERO, VEC3_ZERO, 1);
        //model->texture = texture;
        //model->mesh = mesh2;
        program_unistr_mat(program, "u_model", model->mat);

        vec3 p = {0, 0, 4};
        camera_view(camera, p, 0, 0, 0);
        program_unistr_mat(program, "u_view", camera->viewMat);
        render_model(model);

        display_show(display);
    }

    inst_model_free(inst_model);
    texture_free(texture);
    mesh_free(mesh);

    framebuffer_free(framebuffer);

    camera_free(camera);
    program_free(program);
    display_free(display);
}

//deprecated
void test_quad() {
    //display
    const int WIDTH = 640;
    const int HEIGHT = 480;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, 0);
    display_set_icon(display, "data/icon.png");

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    quad_model_t *quad_model = quad_model_new(texture, 0.5f, 0.5f, 0.5f, 0.5f);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, 0);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        program_unistr_mat(program, "u_view", camera->viewMat);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        render_quad(quad_model);

        display_show(display);
    }

    quad_model_free(quad_model);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}

void test_new_viewport() {
    //display
    const int WIDTH = 800;
    const int HEIGHT = 640;
    float renderSize = 2.2f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 1, renderSize);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = 0.1f;
    CLEAR_COLOR[1] = 0.1f;
    CLEAR_COLOR[2] = 0.1f;
    CLEAR_COLOR[3] = 0.1f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    mesh_t *mesh = mesh_newobj("data/gun.obj");
    model_t *model = model_new(mesh, texture);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderSize);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        if (kb[SDL_SCANCODE_T]) renderSize -= 0.005f;
        if (kb[SDL_SCANCODE_G]) renderSize += 0.005f;

        if (renderSize < 0.005f) renderSize = 0.005f;
        const float _f = renderSize;
        if (renderSize > 3.0f) renderSize = _f;

        dprintf("rs: %f\n", renderSize);

        //render
        program_use(program);

        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                for (int z = 0; z < 4; ++z) {
                    model_mat(model, (float[]) {x * 3, y * 3, z * 3}, (float[]) {0, 0, 0}, 0.8f);
                    program_unistr_mat(program, "u_model", model->mat);
                    render_model(model);
                }
            }
        }

        display_show(display);
    }

    model_free(model);
    mesh_free(mesh);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}

void test_math() {
    vec3 v;
    vec3_zero(v);
    vec3_print(v);

    vec3_set(v, 11, 22, 33);
    vec3_print(v);
}

//deprecated
void test_tex_speed() {
    //display
    const int WIDTH = 640;
    const int HEIGHT = 480;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, 0);

#define TEX_NUM 1

    Uint32 start = SDL_GetTicks();

    texture_t *texs[TEX_NUM];

    for (int i = 0; i < TEX_NUM; ++i) {
        texs[i] = texture_new("data/large.png", GL_LINEAR, 1);
    }

    for (int i = 0; i < TEX_NUM; ++i) {
        texture_free(texs[i]);
    }

    printf("time: %d\n", SDL_GetTicks() - start);

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) WIDTH / HEIGHT, 0.1f, 200);
    program_unistr_mat(program, "u_projection", camera->projMat);


    while (display->running) {
        float delta;
        display_prepare(display, &delta, 0);
        const Uint8 *kb = SDL_GetKeyboardState(NULL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;
        display_show(display);
    }

    camera_free(camera);
    program_free(program);
    display_free(display);
}

void test_tex_wrap() {
    //display
    const int WIDTH = 800;
    const int HEIGHT = 640;
    float renderSize = 1.2f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = 0.1f;
    CLEAR_COLOR[1] = 0.1f;
    CLEAR_COLOR[2] = 0.1f;
    CLEAR_COLOR[3] = 0.1f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    texture_wrap(texture, GL_MIRRORED_REPEAT);
    mesh_t *mesh = mesh_newobj("data/plane.obj");
    model_t *model = model_new(mesh, texture);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderSize);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        if (kb[SDL_SCANCODE_T]) renderSize -= 0.005f;
        if (kb[SDL_SCANCODE_G]) renderSize += 0.005f;

        if (renderSize < 0.005f) renderSize = 0.005f;
        const float _f = renderSize;
        if (renderSize > 3.0f) renderSize = _f;

        dprintf("rs: %f\n", renderSize);

        //render
        program_use(program);

        static float rot = 0;
        rot += delta * 2;

        for (int x = -5; x < 5; ++x) {
            for (int z = -5; z < 5; ++z) {
                model_mat(model, (float[]) {x * 5, sinf(rot + x + z) * 2, z * 5}, (float[]) {-90.0f, 0, 0}, 0.82f);
                program_unistr_mat(program, "u_model", model->mat);
                render_model(model);
            }
        }

        display_show(display);
    }

    model_free(model);
    mesh_free(mesh);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}

void quad_testing() {
    //display
    const int WIDTH = 700;
    const int HEIGHT = 700;
    float renderScale = 1.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderScale);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = CLEAR_COLOR[1] = CLEAR_COLOR[2] = CLEAR_COLOR[3] = 0.5f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/large.png", GL_NEAREST, 1);
    quad_model_t *quad = quad_model_new(texture, 1, 1, 0.7, 0.7, 45);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderScale);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        program_use(program);

        static float time = 0;
        time += delta;

        quad->dim[0] = sinf(time) / 2;
        quad->dim[1] = sinf(time) / 2;
        quad->rot = cosf(time) * 30;

        render_quad(quad);

        display_show(display);
    }

    quad_model_free(quad);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}

void frustum_testing() {//display
    const int WIDTH = 1600;
    const int HEIGHT = 900;
    float renderSize = 1.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = 0.1f;
    CLEAR_COLOR[1] = 0.1f;
    CLEAR_COLOR[2] = 0.1f;
    CLEAR_COLOR[3] = 0.1f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    mesh_t *mesh = mesh_newobj("data/ico.obj");
    model_t *model = model_new(mesh, texture);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderSize);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //frustum
        frustum_t frustum;
        frustum_projview(frustum, projview);

        //render
        program_use(program);

        static float time = 0;
        time += delta;

        const int N = 5;
        int drawn = 0;

        for (int x = -N; x < N; ++x) {
            for (int y = -N; y < N; ++y) {
                for (int z = -N; z < N; ++z) {
                    vec3 p = {x * 5.3f, y * 5.3f, z * 5.3f};

                    if (frustum_issphere(frustum, p, 1.0f)) {
                        model_mat(model, p, (float[]) {0, 0, 0}, 0.8f);
                        program_unistr_mat(program, "u_model", model->mat);
                        render_model(model);
                        drawn++;
                    }
                }
            }
        }

        printf("drawn: %d\n", drawn);

        display_show(display);
    }

    model_free(model);
    mesh_free(mesh);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}

void check_bug_fixes() {
    //vector norm len = 0 bug
    vec3 v = {0, 1, 1};
    vec3_print(v);
    vec3_norm(v, v);
    vec3_print(v);

    //vec rotate
    puts("");
    vec2 rot = {1, 0};
    vec2_print(rot);
    for (int i = 0; i < 8; ++i) {
        vec2_rot(rot, rot, 45 * DEG_2_RAD);
        vec2_print(rot);
    }
    vec2_print(rot);

}

void control_lookto(vec3 pos, vec3 lookto, float delta) {
    const Uint8 *kb = SDL_GetKeyboardState(NULL);

    static float la = 0;
    la += kb[SDL_SCANCODE_E] * delta * M_2_PI;
    la -= kb[SDL_SCANCODE_Q] * delta * M_2_PI;

    static float vert = 0;
    vert += kb[SDL_SCANCODE_R] * delta;
    vert -= kb[SDL_SCANCODE_F] * delta;

    lookto[0] = cosf(la);
    lookto[1] = vert;
    lookto[2] = sinf(la);

    float ang = atan2f(lookto[2], lookto[0]);

    vec3 move = {0};

    move[0] += kb[SDL_SCANCODE_W];
    move[0] -= kb[SDL_SCANCODE_S];

    move[2] += kb[SDL_SCANCODE_A];
    move[2] -= kb[SDL_SCANCODE_D];

    vec3_norm(move, move);

    vec3 nmove;
    nmove[0] = (cosf(la) * move[0] - sinf(la) * move[2]) * delta * 3;
    nmove[2] = (sinf(la) * move[0] + cosf(la) * move[2]) * delta * 3;

    vec3_add(pos, pos, nmove);
}

void test_camera_lookto() {
    const int WIDTH = 1000;
    const int HEIGHT = 500;
    float renderSize = 1.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = 0.1f;
    CLEAR_COLOR[1] = 0.1f;
    CLEAR_COLOR[2] = 0.1f;
    CLEAR_COLOR[3] = 0.1f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.5f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    mesh_t *mesh = mesh_newobj("data/ico.obj");
    model_t *model = model_new(mesh, texture);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderSize);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        static vec3 pos = {0};
        static vec3 lookto = {0};
        control_lookto(pos, lookto, delta);

        camera_lookto(camera, pos, lookto);

        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //frustum
        frustum_t frustum;
        frustum_projview(frustum, projview);

        //render
        program_use(program);

        static float time = 0;
        time += delta;

        const int N = 15;
        int drawn = 0;

        for (int x = -N; x < N; ++x) {
            for (int z = -N; z < N; ++z) {
                vec3 p = {x * 4.f, -2, z * 4.f};

                if (frustum_issphere(frustum, p, 1.0f)) {
                    model_mat(model, p, (float[]) {0, 0, 0}, 0.8f);
                    program_unistr_mat(program, "u_model", model->mat);
                    render_model(model);
                    drawn++;
                }
            }

        }

        printf("drawn: %d\n", drawn);

        display_show(display);
    }

    model_free(model);
    mesh_free(mesh);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}

#endif

void cam_control(camera_t *camera, float delta) {
    const Uint8 *kb = SDL_GetKeyboardState(NULL);

    static float x = 0;
    static float y = 0;
    static float z = 0;
    vec3 pos = {x, y, z};
    float a = 2 * delta;
    if (kb[SDL_SCANCODE_W]) z -= a;
    if (kb[SDL_SCANCODE_S]) z += a;
    if (kb[SDL_SCANCODE_A]) x -= a;
    if (kb[SDL_SCANCODE_D]) x += a;
    if (kb[SDL_SCANCODE_Q]) y += a;
    if (kb[SDL_SCANCODE_E]) y -= a;
    //printf("pos: %f %f %f\n", x, y, z);

    static float xr = 0;
    static float yr = 0;
    static float zr = 0;
    vec3 rot = {xr, yr, zr};
    float r = 20.0f * delta;
    if (kb[SDL_SCANCODE_I]) xr -= r;
    if (kb[SDL_SCANCODE_K]) xr += r;
    if (kb[SDL_SCANCODE_J]) yr -= r;
    if (kb[SDL_SCANCODE_L]) yr += r;
    if (kb[SDL_SCANCODE_U]) zr += r;
    if (kb[SDL_SCANCODE_O]) zr -= r;
    //printf("rot: %f %f %f\n", xr, yr, zr);

    if (kb[SDL_SCANCODE_R]) {
        xr = yr = zr = 0;
    }

    camera_view(camera, pos, rot[0], rot[1]);
}


void test_new_camera() {
    const int WIDTH = 1000;
    const int HEIGHT = 500;
    float renderSize = 1.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = CLEAR_COLOR[1] = CLEAR_COLOR[2] = CLEAR_COLOR[3] = 0.2f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.07f, 100);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_NEAREST, 1);
    mesh_t *mesh = mesh_newobj("data/ico.obj");
    model_t *model = model_new(mesh, texture);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderSize);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera, delta);

        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //frustum
        frustum_t frustum;
        frustum_projview(frustum, projview);

        //render
        program_use(program);

        static float time = 0;
        time += delta;

        const int N = 5;

        for (int x = -N; x < N; ++x) {
            for (int z = -N; z < N; ++z) {
                vec3 p = {x * 4.f, -2, z * 4.f};

                if (frustum_issphere(frustum, p, 1.0f)) {
                    model_mat(model, p, (float[]) {0, 0, 0}, 0.8f);
                    program_unistr_mat(program, "u_model", model->mat);
                    render_model(model);
                }
            }

        }

        display_show(display);
    }

    model_free(model);
    mesh_free(mesh);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int iCmdShow) {
    test_new_camera();

    return 0;
}