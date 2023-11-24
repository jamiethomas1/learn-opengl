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

void VertexArray::bind()
{
    glBindVertexArray(this->id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
