//
// Created by Thomas Lienbacher on 22.01.2018.
//

#ifndef TENGINE_RENDER_H
#define TENGINE_RENDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "master.h"
#include "mesh.h"
#include "tengine_math.h"
#include "program.h"
#include "model.h"
#include "text.h"

extern vec4 CLEAR_COLOR;

void _render_init_quadshader();

void _render_quit_quadshader();

void render_begin();

void render_model(model_t *model);

void render_same_model(model_t *model);

void render_instanced_dyn(model_t *model, program_t *program, int count,
                          mat4x4 *mats);//creates a new buffer and removes it afterwards

void render_inst_model(inst_model_t *inst_model, program_t *program);

void render_quad(quad_model_t *quad_model);

void render_text(text_t *text);

void render_end();

#ifdef __cplusplus
}
#endif

#endif //TENGINE_RENDER_H
