#pragma once

#include "renderer.h"
#include <vector>

class VertexBuffer
{
private:
    GLuint m_ID;

public:
    VertexBuffer(const void *data, GLuint size);
    VertexBuffer(const std::vector<float> vertices, GLuint size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};