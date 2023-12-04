#include "vertexBuffer.h"

#include <iostream>
#include <glad/glad.h>


/**
 * @brief Generate & bind VertexBuffer object
*/
VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}


/**
 * @brief Wrapper for glDeleteBuffers
*/
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}


/**
 * @brief Wrapper for glBindBuffer
*/
const void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}


/**
 * @brief Wrapper for glBindBuffer
*/
const void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/**
 * @brief Add vector of vertices to the vertex buffer. Calls glBufferData
 * @param vertices The vector of vertices
*/
void VertexBuffer::setData(std::vector<float> vertices)
{
    m_Vertices = vertices;
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), static_cast<const void*>(m_Vertices.data()), GL_STATIC_DRAW);
}
