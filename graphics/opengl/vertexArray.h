#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_ID;

public:
    VertexArray();
    ~VertexArray();

    const void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;
    const void bind() const;
    const void unbind() const;
};