#include "vertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();

    const auto &elements = layout.getElements();
    GLuint offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind()
{
    glBindVertexArray(m_ID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
