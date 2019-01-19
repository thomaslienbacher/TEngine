//
// Created by Thomas Lienbacher on 25.02.2018.
//

#include <stdlib.h>
#include "framebuffer.h"
#include "texture.h"
#include "utils.h"
#include "render.h"

framebuffer_t *framebuffer_new(int width, int height) {
    framebuffer_t *framebuffer = calloc(1, sizeof(framebuffer_t));
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->originalWidth = width;
    framebuffer->originalHeight = height;

    //texture
    texture_t *texture = calloc(1, sizeof(texture_t));
    framebuffer->texture = texture;

    texture->width = width;
    texture->height = height;

    //opengl
    glGenFramebuffers(1, &framebuffer->id);
    framebuffer_bind(framebuffer);

    //texture
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //depth attachment
    GLuint depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

    //color attachment
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->id, 0);
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        dief("Framebuffer: framebuffer not complete: %d", framebuffer->id);

    return framebuffer;
}

static unsigned int bound = 0;

void framebuffer_bind(framebuffer_t *framebuffer) {
    if (framebuffer == NULL) {
        if (bound) {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            bound = 0;
        }
    } else if (framebuffer->id != bound) {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer->id);

        if (framebuffer->width > framebuffer->originalWidth || framebuffer->height > framebuffer->originalHeight) {
            dief("Framebuffer: size bigger than originalsize: %d > %d || %d > %d",
                 framebuffer->width, framebuffer->originalWidth,
                 framebuffer->height, framebuffer->originalHeight);
        }

        glViewport(0, 0, framebuffer->width, framebuffer->height);
        bound = framebuffer->id;
    }
}

void framebuffer_clear(framebuffer_t *framebuffer) {
    framebuffer_bind(framebuffer);
    glClearColor(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void framebuffer_free(framebuffer_t *framebuffer) {
    texture_free(framebuffer->texture);
    glDeleteFramebuffers(1, &framebuffer->id);
    free(framebuffer);
}