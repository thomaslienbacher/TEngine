//
// Created by Thomas Lienbacher on 25.01.2018.
//

/**
 * version: 1.1
 */

#include <stdlib.h>
#include "texture.h"
#include "utils.h"
#include "filehelper.h"

static float maxAniso = -1;

texture_t* texture_new(FILE* texFile, GLenum filter, float aniso){
    texture_t* texture = calloc(1, sizeof(texture_t));

    unsigned error;
    unsigned char* image;
    unsigned width, height;

    unsigned long fileLen = 0;
    char* fileData = NULL;
    fadv_info(texFile, &fileLen, &fileData);

    error = lodepng_decode32(&image, &width, &height, (unsigned char*)fileData, fileLen);
    free(fileData);
    if(error) dief("Loading Texture: %s", lodepng_error_text(error));

    //opengl
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter == GL_NEAREST ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glGenerateMipmap(GL_TEXTURE_2D);

    //get anisotropic filtering
    if(GLEW_EXT_texture_filter_anisotropic){
        if(maxAniso < 0) glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso > maxAniso ? maxAniso : aniso);
    }

    free(image);

    return texture;
}

static unsigned int bound = 0;

void texture_bind(texture_t* texture){
    if(texture == NULL){
        glBindTexture(GL_TEXTURE_2D, 0);
        bound = 0;
    }
    else if(texture->id != bound) {
        glBindTexture(GL_TEXTURE_2D, texture->id);
        bound = texture->id;
    }
}

void texture_free(texture_t* texture){
    texture_bind(NULL);
    glDeleteTextures(1, &texture->id);
    free(texture);
}