#include "model.h"

#include <iostream>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()


/**
 * @brief Initialise a Model object with a position
 * @param position Vec3 denoting position of model
 */
Model::Model(const glm::vec3 position)
    : m_Position(position)
{
    m_Layout.push(GL_FLOAT, 3);
    m_Layout.push(GL_FLOAT, 2);
    modelTransform();
}


/**
 * @brief Generates a translation matrix for positioning the model in the world
 */
void Model::modelTransform()
{
    m_ModelMatrix = glm::mat4(1.f);
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
}


/**
 * @brief Renders model on screen. Calls Renderable::render()
 */
const void Model::render() const {
    Renderable::render(m_IB.getCount());
}