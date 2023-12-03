#include "model.h"

#include <iostream>

// ? If possible to do without messing up inheritance, this could be simplified by making the position parameter in the next overload optional
Model::Model()
    : m_Position(0.f, 0.f, 0.f)
{
    m_Layout.push(GL_FLOAT, 3);
    m_Layout.push(GL_FLOAT, 2);
    modelTransform();
}

Model::Model(const glm::vec3 position)
    : m_Position(position)
{
    m_Layout.push(GL_FLOAT, 3);
    m_Layout.push(GL_FLOAT, 2);
    modelTransform();
}

void Model::modelTransform()
{
    m_ModelMatrix = glm::mat4(1.f);
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
}

const void Model::render() const {
    Renderable::render(m_IB.getCount());
}