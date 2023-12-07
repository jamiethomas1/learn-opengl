#include "indexBuffer.h"

#include <iostream>
#include <glad/glad.h>
#include "checkGLErrors.h"


/**
 * @brief Generates and binds an element array buffer
*/
IndexBuffer::IndexBuffer()
{
    GL_CALL(glGenBuffers(1, &m_ID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}


/**
 * @brief Wrapper for glDeleteBuffers
*/
IndexBuffer::~IndexBuffer()
{
    GL_CALL(glDeleteBuffers(1, &m_ID));
}


/**
 * @brief Wrapper for glBindBuffers
*/
const void IndexBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}


/**
 * @brief Wrapper for glBindBuffers
*/
const void IndexBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


/**
 * @brief Add vector of indices to the index buffer. Calls glBufferData
 * @param indices The vector of indices
*/
void IndexBuffer::setData(const std::vector<unsigned int> indices)
{
    m_Indices = indices;
    m_Count = indices.size();
    bind();
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), static_cast<const void*>(m_Indices.data()), GL_STATIC_DRAW));
}
