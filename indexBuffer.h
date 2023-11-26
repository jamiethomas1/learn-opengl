#pragma once

#include "renderer.h"

class IndexBuffer
{
private:
    GLuint m_ID;
    GLuint m_Count;

public:
    IndexBuffer(const GLuint *data, const GLuint count);
    ~IndexBuffer();
    void bind();
    void unbind();

    const GLuint getCount() const { return m_Count; }
};