#include "renderable.h"

#include "glad/glad.h"

Renderable::Renderable()
{
}

const void Renderable::render(const unsigned int indicesCount) const {
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}