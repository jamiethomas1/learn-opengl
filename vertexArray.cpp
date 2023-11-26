#include "vertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->id);
    glBindVertexArray(this->id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &this->id);
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
    glBindVertexArray(this->id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
