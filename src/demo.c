#include <stdio.h>
#include <assert.h>
#include "tengine_math.h"
#include "master.h"
#include "display.h"
#include "program.h"
#include "camera.h"
#include "render.h"
#include "frustum.h"
#include "vector.h"

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
    float r = FM_PI_2 * RAD_2_DEG * delta;
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

#define __REMOVE_FROM_COMPILATION__
#ifndef  __REMOVE_FROM_COMPILATION__

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

void print_fb() {
    GLint drawFboId = 0, readFboId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

    fflush(stdout);
    fflush(stderr);

    dprintf("fb: draw: %d read: %d\n", drawFboId, readFboId);
}

void test_new_viewport() {
    //display
    const int WIDTH = 800;
    const int HEIGHT = 640;
    float renderSize = 2.2f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 1, renderSize, 1);
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

        cam_control(camera, delta);
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
                    model_transform(model, (float[]) {x * 3, y * 3, z * 3}, (float[]) {0, 0, 0}, 0.8f);
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

void test_tex_wrap() {
    //display
    const int WIDTH = 800;
    const int HEIGHT = 640;
    float renderSize = 1.2f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize, 1);
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

        cam_control(camera, delta);
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
        if (renderSize > 1.2) renderSize = _f;

        dprintf("rs: %f\n", renderSize);

        //render
        program_use(program);

        static float rot = 0;
        rot += delta * 2;

        for (int x = -5; x < 5; ++x) {
            for (int z = -5; z < 5; ++z) {
                model_transform(model, (float[]) {x * 5, sinf(rot + x + z) * 2, z * 5}, (float[]) {-90.0f, 0, 0},
                                0.82f);
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
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderScale, 1);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = CLEAR_COLOR[1] = CLEAR_COLOR[2] = CLEAR_COLOR[3] = 0.5f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(80, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_LINEAR, 1);
    quad_model_t *quad = quad_model_new(texture, 1, 0, 1, 1, 0);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderScale);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera, delta);
        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        program_use(program);

        static float time = 0;
        time += delta;

        //quad->dim[0] = 0.5;
        quad->dim[2] = fabsf(cosf(time));
        quad->dim[3] = fabsf(cosf(time));
        //quad->dim[1] = sinf(time) / 2.f;
        quad->rot = time * 90;

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
    float renderSize = 2.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize, 0);
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
    texture_t *texture = texture_new("data/gun.png", GL_LINEAR, 4.0f);
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

        const int N = 6;
        int drawn = 0;

        for (int x = -N; x < N; ++x) {
            for (int y = -N; y < N; ++y) {
                for (int z = -N; z < N; ++z) {
                    vec3 p = {x * 5.3f, y * 5.3f, z * 5.3f};

                    if (frustum_issphere(frustum, p, 1.0f)) {
                        model_transform(model, p, (float[]) {0, 0, 0}, 0.8f);
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

void test_new_camera_and_all_axis_scaling() {
    const int WIDTH = 1600;
    const int HEIGHT = 900;
    float renderSize = 2.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize, 1);
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
        float sin = (sinf(time * 1.8f) + 1) / 2.0f + 0.5f;
        float cos = (cosf(time * 1.5f) + 1) / 2.0f + 0.5f;

        const int N = 5;

        for (int x = -N; x < N; ++x) {
            for (int z = -N; z < N; ++z) {
                vec3 p = {x * 4.f, -2, z * 4.f};

                if (frustum_issphere(frustum, p, 1.0f)) {
                    model_transformd_as(model->mat, p, (float[]) {sinf(time / x) * 360.0f, sinf(time / z) * 360.0f, 0}, (float[]) {sin, cos, sin * cos});
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



void test_text_rendering() {
    const int WIDTH = 900;
    const int HEIGHT = 900;
    float renderSize = 1.0f;
    display_t *display = display_new("OpenGL", WIDTH, HEIGHT, 0, renderSize, 1);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = CLEAR_COLOR[1] = CLEAR_COLOR[2] = CLEAR_COLOR[3] = 0.3f;

    //program
    program_t *program = program_new("data/font_vs.glsl", "data/font_fs.glsl");
    program_use(program);

    //font
    font_t *fontA = font_new("data/consolas_32.csv", "data/consolas_32.png", FONT_DEFAULT_SCALAR);
    font_t *fontB = font_new("data/franklingb_44.csv", "data/franklingb_44.png", FONT_DEFAULT_SCALAR);
    font_t *fontC = font_new("data/harrington_55.csv", "data/harrington_55.png", FONT_DEFAULT_SCALAR);
    //font_t *fontC = font_new("data/broadway_46.csv", "data/broadway_46.png", FONT_DEFAULT_SCALAR);

    //text
    text_t *textA = text_new(fontA, "A Thomas 3245 _:;-$o");
    text_t *textB = text_new(fontB, "B Thomas 3245 _:;-$o");
    text_t *textC = text_new(fontC, "C Thomas 3245 _:;-$o");

    while (display->running) {
        float delta;
        display_prepare(display, &delta, renderSize);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        program_use(program);

        static float time = 0;
        time += delta;

        float scale = mclamp(sinf(time * 2) + 1.2f, 1.0, 3.0);

        text_transform(textA, (float[]) {-textA->width / 2, 0.3}, scale);
        text_transform(textB, (float[]) {-textB->width / 2, 0}, scale);
        text_transform(textC, (float[]) {-textC->width / 2, -0.3f}, scale);

        //render text
        program_unistr_mat(program, "u_transform", textA->mat);
        render_text(textA);

        program_unistr_mat(program, "u_transform", textB->mat);
        render_text(textB);

        program_unistr_mat(program, "u_transform", textC->mat);
        render_text(textC);

        display_show(display);
    }

    text_free(textA);
    text_free(textB);
    text_free(textC);
    font_free(fontA);
    font_free(fontB);
    font_free(fontC);
    program_free(program);
    display_free(display);
}

void test_generic_math() {
    {
        float fi = mmin(5.0f, 1.0f);
        printf("mmin(5.0f, 1.0f) = %f\n", fi);
        assert(fi == 1.0f);

        float fa = mmax(5.0f, 1.0f);
        printf("mmax(5.0f, 1.0f) = %f\n", fa);
        assert(fa == 5.0f);

        float fl = mclamp(5.0f, 1.0f, 3.0f);
        printf("mclamp(5.0f, 1.0f, 3.0f) = %f\n", fl);
        assert(fl == 3.0f);
    }
    {
        int i = mmin(5, 1);
        printf("mmin(5, 1) = %d\n", i);
        assert(i == 1);

        int a = mmax(5, 1);
        printf("mmax(5, 1) = %d\n", a);
        assert(a == 5);

        int l = mclamp(5, 1, 3);
        printf("mclamp(5, 1, 3) = %d\n", l);
        assert(l == 3);
    }
    {
        long i = mmin(5l, 1l);
        printf("mmin(5l, 1l) = %ld\n", i);
        assert(i == 1l);

        long a = mmax(5l, 1l);
        printf("mmax(5l, 1l) = %ld\n", a);
        assert(a == 5l);

        long l = mclamp(5l, 1l, 3l);
        printf("mclamp(5l, 1l, 3l) = %ld\n", l);
        assert(l == 3l);
    }
    {
        double i = mmin(5.0, 1.0);
        printf("mmin(5.0, 1.0) = %f\n", i);
        assert(i == 1.0);

        double a = mmax(5.0, 1.0);
        printf("mmax(5.0, 1.0) = %f\n", a);
        assert(a == 5.0);

        double l = mclamp(5.2, 1.1, 3.0);
        printf("mclamp(5.2, 1.1, 3.0) = %f\n", l);
        assert(l == 3.0);
    }
}

#endif

void print_vec_addrtrim(vector_t *vec) {
    for (int j = 0; j < vec->size; ++j) {
        int *d = ((int *) vector_get(vec, j));
        printf("%d -> %x -> ", j, d);
        if (d) printf("%d\n", *d);
        else printf("\n");
    }
}

void test_vector_resize() {
    vector_t *vec = vector_new(10);

    for (int i = 0; i < 30; ++i) {
        int *d = malloc(sizeof(int));
        *d = i * i;
        vector_push(vec, d);
        printf("%d -> size: %lld\n", i, vec->size);
    }

    vector_realloc(vec, 200);

    for (int i = 0; i < 230; ++i) {
        int *d = malloc(sizeof(int));
        *d = i * i;
        vector_push(vec, d);
        printf("%d -> size: %lld\n", i, vec->size);
    }

    print_vec_addrtrim(vec);
    vector_realloc(vec, 170);

    free(vector_remove(vec, 1));
    free(vector_remove(vec, 2));
    free(vector_remove(vec, 3));

    print_vec_addrtrim(vec);

    for (int k = 0; k < 40; ++k) {
        free(vector_remove(vec, 10 + k));
    }

    print_vec_addrtrim(vec);
    vector_trim(vec);
    print_vec_addrtrim(vec);

    for (int j = 0; j < vec->size; ++j) {
        free(vector_remove(vec, j));
    }

    print_vec_addrtrim(vec);
    vector_free(vec);
}

int main(int argc, char *argv[]) {
    //test_vector();
    //test_new_viewport();
    //test_tex_wrap();
    //quad_testing();
    //frustum_testing();
    //test_new_camera_and_all_axis_scaling();
    //test_text_rendering();
    //test_generic_math();

    test_vector_resize();

    return 0;
}