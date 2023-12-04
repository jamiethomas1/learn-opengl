#include "vertexArray.h"

#include <glad/glad.h>


/**
 * @brief Generate & bind VertexArray object
*/
VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
}


/**
 * @brief Wrapper for glDeleteVertexArrays
*/
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}


/**
 * @brief Add a new VertexBuffer to the VertexArray
 * @param vb The VertexBuffer to be added
 * @param layout Layout object containing info about that buffer's data structure
*/
const void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const
{
    bind();
    vb.bind();

    const auto &elements = layout.getElements();
    int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)(uintptr_t)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}


/**
 * @brief Wrapper for glBindVertexArray
*/
const void VertexArray::bind() const
{
    glBindVertexArray(m_ID);
}


/**
 * @brief Wrapper for glBindVertexArray
*/
const void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
