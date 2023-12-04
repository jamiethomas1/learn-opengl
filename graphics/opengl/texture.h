#pragma once


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
    Texture(const char *path, const unsigned int textureUnit, const unsigned int format);
    ~Texture();

    const void bind() const;
    const void unbind() const;
};