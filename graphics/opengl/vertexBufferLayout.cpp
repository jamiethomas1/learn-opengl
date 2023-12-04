#include "vertexBufferLayout.h"

#include <glad/glad.h>


/**
 * @brief Make space in the vertex buffer for some data
 * @param type (GLenum) The type of the incoming data
 * @param count How many of the aforementioned data type will be stored
*/
void VertexBufferLayout::push(const unsigned int type, const unsigned int count)
{
    m_Elements.push_back({type, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::getSizeOfType(type);
}
