#include "vertexBuffer.h"

#include <iostream>
#include <glad/glad.h>


VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

VertexBuffer::VertexBuffer(const void *data, const unsigned int size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

VertexBuffer::VertexBuffer(const std::vector<float> vertices, const unsigned int size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

const void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

const void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(std::vector<float> vertices)
{
    m_Vertices = vertices;
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), static_cast<const void*>(m_Vertices.data()), GL_STATIC_DRAW);
}
