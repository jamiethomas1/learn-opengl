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
    const Image *m_Image;
    const GLuint m_TextureUnit;
    const char *m_Path;

    const Image* loadImage() const;

public:
    Texture(const char *path, const GLuint textureUnit, const GLenum format);
    ~Texture();

    const void bind() const;
    const void unbind() const;
};