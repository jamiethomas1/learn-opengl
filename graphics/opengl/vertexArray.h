#pragma once

#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
private:
    GLuint m_ID;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
    void bind();
    void unbind();
};