#include "texture.h"
#include "stb_image.h"

#include "checkGLErrors.h"

#include <iostream>


/**
 * @brief Read image file as raw data into Image object
 * @return Pointer to Image object
*/
const Image* Texture::loadImage() const
{
    Image *image = new Image({0, 0, 0, m_Path, nullptr});
    image->data = stbi_load(image->path, &image->width, &image->height, &image->nrChannels, 0);
    return image;
}


/**
 * @brief Generate, bind, and prepare a Texture object
 * @param path Path to image file
 * @param textureUnit (GLenum) OpenGL texture unit e.g. GL_TEXTURE0
 * @param format (GLenum) Colour format e.g. GL_RGBA
*/
Texture::Texture(const char *path, const unsigned int textureUnit)
    : m_Path(path), m_TextureUnit(textureUnit)
{
    stbi_set_flip_vertically_on_load(true);
    m_Image = loadImage();

    GL_CALL(glGenTextures(1, &m_ID));
    GL_CALL(glActiveTexture(m_TextureUnit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ID));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    unsigned int format = GL_RGB;
    if (m_Image->nrChannels == 4) format = GL_RGBA;

    if (m_Image->data) {
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Image->width, m_Image->height, 0, format, GL_UNSIGNED_BYTE, m_Image->data));
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cout << "Failed to load texture: " << path << std::endl;
        m_Path = "res/default.jpg";
        m_Image = loadImage();
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Image->width, m_Image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Image->data));
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    }
}


/**
 * @brief Wrapper for glDeleteTextures
*/
Texture::~Texture()
{
    GL_CALL(glDeleteTextures(1, &m_ID));
}


/**
 * @brief Wrapper for glBindTexture
*/
const void Texture::bind() const // ? could call bind(texUnit) with say GL_TEXTURE0 so it's more flexible
{
    GL_CALL(glActiveTexture(m_TextureUnit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ID));
}


/**
 * @brief Wrapper for glBindTexture
*/
const void Texture::unbind() const
{
    GL_CALL(glActiveTexture(m_TextureUnit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
