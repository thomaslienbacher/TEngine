//
// Created by Thomas Lienbacher on 25.01.2018.
//

#include <stdlib.h>
#include "texture.h"
#include "utils.h"
#include "filehelper.h"

static float maxAniso = -1;

texture_t *texture_newf(FILE *texFile, GLenum filter, float aniso) {
    texture_t *texture = calloc(1, sizeof(texture_t));

    unsigned error;
    unsigned char *image;
    unsigned width, height;

    size_t fileLen = 0;
    char *fileData = NULL;
    fadv_info(texFile, &fileLen, &fileData);

    error = lodepng_decode32(&image, &width, &height, (unsigned char *) fileData, fileLen);

    free(fileData);
    if (error) dief("Loading Texture: %s", lodepng_error_text(error));

    texture->width = width;
    texture->height = height;

    //opengl
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter == GL_NEAREST ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glGenerateMipmap(GL_TEXTURE_2D);

    //get anisotropic filtering
    if (GLEW_EXT_texture_filter_anisotropic) {
        if (maxAniso < 0) glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
        if (aniso < 1) dief("Texture: anisotropic filtering value to small: %f", aniso);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso > maxAniso ? maxAniso : aniso);
    }

    free(image);

    return texture;
}

texture_t *texture_new(const char *file, GLenum filter, float aniso) {
    FILE *tex = fadv_open(file, "rb");
    texture_t *texture = texture_newf(tex, filter, aniso);
    fadv_close(tex);

    return texture;
}

static unsigned int bound = 0;

void texture_wrap(texture_t *texture, GLint wrap) {
    texture_bind(texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
}

void texture_bind(texture_t *texture) {
    if (texture == NULL) {
        if (bound) {
            glBindTexture(GL_TEXTURE_2D, 0);
            bound = 0;
        }
    } else if (texture->id != bound) {
        glBindTexture(GL_TEXTURE_2D, texture->id);
        bound = texture->id;
    }
}

void texture_free(texture_t *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}