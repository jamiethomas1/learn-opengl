#pragma once

#include "renderer.h"

struct Image {
    int width;
    int height;
    int nrChannels;
    const char *path;
    unsigned char *data;
};

class Texture {
private:
    GLuint m_ID;
    Image *m_Image;
    GLuint m_TextureUnit;
    const char *m_Path;

    Image* loadImage();

public:
    Texture(const char *path, GLuint textureUnit, GLenum format);
    ~Texture();

    void bind();
    void unbind();
};