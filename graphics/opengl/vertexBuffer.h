#pragma once

#include "renderer.h"
#include <vector>

class VertexBuffer
{
private:
    GLuint m_ID;
    std::vector<float> m_Vertices;

public:
    VertexBuffer();
    VertexBuffer(const void *data, const GLuint size);
    VertexBuffer(const std::vector<float> vertices, const GLuint size);
    ~VertexBuffer();

    const void bind() const;
    const void unbind() const;

    void setData(std::vector<float> vertices);
};