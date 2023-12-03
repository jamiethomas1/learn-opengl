#include "vertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
    : m_Stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

void VertexBufferLayout::push(const GLuint type, const GLuint count)
{
    m_Elements.push_back({type, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::getSizeOfType(type);
}
