#pragma once

#include <glad/glad.h>


struct Image {
    int width;
    int height;
    int nrChannels;
    const char *path;
    unsigned char *data;
};


class Texture {
private:
    unsigned int m_ID;
    const Image *m_Image;
    const unsigned int m_TextureUnit;
    const char *m_Path;

    const Image* loadImage() const;

public:
    Texture() : Texture("res/default.jpg", GL_TEXTURE0) {}
    Texture(const char *path, const unsigned int textureUnit);
    ~Texture();

    const void bind() const;
    const void unbind() const;
};