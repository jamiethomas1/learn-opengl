#include "texture.h"
#include "stb_image.h"
#include <iostream>

const Image* Texture::loadImage() const
{
    Image *image = new Image({0, 0, 0, m_Path, nullptr});
    image->data = stbi_load(image->path, &image->width, &image->height, &image->nrChannels, 0);
    return image;
}

Texture::Texture(const char *path, const GLuint textureUnit, const GLenum format)
    : m_Path(path), m_TextureUnit(textureUnit)
{
    stbi_set_flip_vertically_on_load(true);
    m_Image = loadImage();

    glGenTextures(1, &m_ID);
    glActiveTexture(m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_Image->data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Image->width, m_Image->height, 0, format, GL_UNSIGNED_BYTE, m_Image->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

const void Texture::bind() const // ? could call bind(texUnit) with say GL_TEXTURE0 so it's more flexible
{
    glActiveTexture(m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

const void Texture::unbind() const
{
    glActiveTexture(m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}
