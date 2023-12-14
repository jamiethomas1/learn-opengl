#include "light.h"

#include <iostream>
#include <assert.h>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/gtx/string_cast.hpp>

#include "opengl/renderer.h"

#include <glad/glad.h> //! Temporary. Remove all references to GL enums in the Model class.


/**
 * @brief Initialise a Light object with a position
 * @param position Vec3 denoting position of model
 */
Light::Light(const glm::vec3 position)
    : m_Position(position)
    , m_RotationMatrix(glm::mat4(1.f))
    , m_Shader(new Shader("shaders/vDefaultLight.glsl", "shaders/fDefaultLight.glsl"))
{
    setPosition(m_Position);
    
    m_Layout.push(GL_FLOAT, 3);

    m_Shader->use();

    Renderer::push(this);
}


/**
 * @brief Set position of Light
 * @param position Vec3 denoting position of model
 */
void Light::setPosition(const glm::vec3 position)
{
    m_Position = position;
    m_ModelMatrix = glm::translate(glm::mat4(1.f), m_Position);
}


/**
 * @brief Set rotation of Light
 * @param angle Rotation angle
 * @param axis Axis of rotation
 */
void Light::setRotation(const float angle, const glm::vec3 axis)
{
    m_RotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
    m_ModelMatrix *= m_RotationMatrix;
    setPosition(m_Position); // Have to reset position after rotating
}


/**
 * @brief Set rotation of Light
 * @param rotationMatrix Matrix to rotate model with
 */
void Light::setRotation(glm::mat4& rotationMatrix)
{
    m_RotationMatrix = rotationMatrix;
    m_ModelMatrix *= m_RotationMatrix;
    setPosition(m_Position); // Have to reset position after rotating
}


/**
 * @brief Set the scale of the Light
 * @param scaleFactor What to scale the dimensions by
*/
void Light::setScale(const float scaleFactor)
{
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(scaleFactor));
}

/**
 * @brief Move model with given translation vector
 * @param movement Translation vector
 */
void Light::move(glm::vec3 &movement)
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(movement));
    move(translationMatrix);
}


/**
 * @brief Move model with given translation matrix
 * @param translationMatrix Matrix to translate model with
 */
void Light::move(glm::mat4 &translationMatrix)
{
    m_ModelMatrix = translationMatrix * m_ModelMatrix;
}

/**
 * @brief Rotate model by given angle around given axis
 * @param angle Rotation angle
 * @param axis Axis of rotation
 */
void Light::rotate(float angle, const glm::vec3 &axis)
{
    m_RotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
    m_ModelMatrix *= m_RotationMatrix;
}


/**
 * @brief Rotate model with given rotation matrix
 * @param rotationMatrix Rotation matrix to be used
 * @bug I believe the sum below is incorrect
 */
void Light::rotate(glm::mat4& rotationMatrix)
{
    m_RotationMatrix = rotationMatrix;
    m_ModelMatrix *= m_RotationMatrix;
}


/**
 * @brief Renders model on screen. Calls Renderable::render()
 */
void Light::render() {
    Renderable::render(m_IB.getCount());
}