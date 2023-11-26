#include "vertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void *data, GLuint size)
{
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &this->id);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
