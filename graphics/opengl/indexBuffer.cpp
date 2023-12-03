#include "indexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

IndexBuffer::IndexBuffer(const GLuint *data, const GLuint count)
    : m_Count(count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int> indices, const GLuint count)
    : m_Count(count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

const void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

const void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(const std::vector<unsigned int> indices)
{
    m_Indices = indices;
    m_Count = indices.size();
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), static_cast<const void*>(m_Indices.data()), GL_STATIC_DRAW);
}
