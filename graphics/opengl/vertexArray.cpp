#include "vertexArray.h"

#include <glad/glad.h>
#include "checkGLErrors.h"


/**
 * @brief Generate & bind VertexArray object
*/
void VertexArray::init() 
{
    GL_CALL(glGenVertexArrays(1, &m_ID));
    GL_CALL(glBindVertexArray(m_ID));    
}


/**
 * @brief Wrapper for glDeleteVertexArrays
*/
void VertexArray::cleanup()
{
    GL_CALL(glDeleteVertexArrays(1, &m_ID));
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
        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)(uintptr_t)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}


/**
 * @brief Wrapper for glBindVertexArray
*/
const void VertexArray::bind() const
{
    GL_CALL(glBindVertexArray(m_ID));
}


/**
 * @brief Wrapper for glBindVertexArray
*/
const void VertexArray::unbind() const
{
    GL_CALL(glBindVertexArray(0));
}
