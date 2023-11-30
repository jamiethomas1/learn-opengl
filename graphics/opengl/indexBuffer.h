#pragma once

#include "renderer.h"
#include <vector>

class IndexBuffer
{
private:
    GLuint m_ID;
    GLuint m_Count;

public:
    IndexBuffer(const GLuint *data, const GLuint count);
    IndexBuffer(const std::vector<unsigned int> indices, const GLuint count);
    ~IndexBuffer();
    void bind();
    void unbind();

    const GLuint getCount() const { return m_Count; }
};