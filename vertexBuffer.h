#pragma once

#include "renderer.h"

class VertexBuffer
{
private:
    GLuint m_ID;

public:
    VertexBuffer(const void *data, GLuint size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};