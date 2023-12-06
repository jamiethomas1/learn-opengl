#include "model.h"

#include <iostream>
#include <assert.h>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h> //! Temporary. Remove all references to GL enums in the Model class.


/**
 * @brief Initialise a Model object with a position
 * @param position Vec3 denoting position of model
 */
Model::Model(const glm::vec3 position)
    : m_Position(position)
    , m_RotationMatrix(glm::mat4(1.f))
    , m_Shader("shaders/vertex.glsl", "shaders/fragment.glsl")
{
    setPosition(m_Position);
    
    m_Layout.push(GL_FLOAT, 3);
    m_Layout.push(GL_FLOAT, 2);

    m_Shader.use();
    m_Shader.setInt("tex", 0);
}


/**
 * @brief Push a Texture to the Model's vector of Textures
 * @param texturePath Path to the image file
 * @note Passing a default constructor Texture() will result in the default texture
 */
void Model::addTexture(const char* texturePath)
{
    assert(m_TextureVector.size() < 16);
    
    m_TextureVector.push_back(new Texture(texturePath, GL_TEXTURE0 + m_TextureVector.size()));
}


/**
 * @brief Loop through texture vector and call bind() on each. Also sends texture to shader.
 */
const void Model::bindTextures() const
{
    for (unsigned int i = 0; i < m_TextureVector.size(); i++) {
        m_TextureVector[i]->bind();
        m_Shader.use();
        m_Shader.setInt("textures[" + std::to_string(i) + "]", i);
    }
}


/**
 * @brief Set position of Model
 * @param position Vec3 denoting position of model
 */
void Model::setPosition(const glm::vec3 position)
{
    m_Position = position;
    m_ModelMatrix = glm::translate(glm::mat4(1.f), m_Position);
}


/**
 * @brief Set rotation of Model
 * @param angle Rotation angle
 * @param axis Axis of rotation
 */
void Model::setRotation(const float angle, const glm::vec3 axis)
{
    m_RotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
    m_ModelMatrix *= m_RotationMatrix;
    setPosition(m_Position); // Have to reset position after rotating
}


/**
 * @brief Set rotation of Model
 * @param rotationMatrix Matrix to rotate model with
 */
void Model::setRotation(glm::mat4& rotationMatrix)
{
    m_RotationMatrix = rotationMatrix;
    m_ModelMatrix *= m_RotationMatrix;
    setPosition(m_Position); // Have to reset position after rotating
}


/**
 * @brief Move model with given translation vector
 * @param movement Translation vector
 */
void Model::move(glm::vec3 &movement)
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(movement));
    move(translationMatrix);
}


/**
 * @brief Move model with given translation matrix
 * @param translationMatrix Matrix to translate model with
 */
void Model::move(glm::mat4 &translationMatrix)
{
    m_ModelMatrix = translationMatrix * m_ModelMatrix;
}

/**
 * @brief Rotate model by given angle around given axis
 * @param angle Rotation angle
 * @param axis Axis of rotation
 */
void Model::rotate(float angle, const glm::vec3 &axis)
{
    m_RotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
    m_ModelMatrix *= m_RotationMatrix;
}


/**
 * @brief Rotate model with given rotation matrix
 * @param rotationMatrix Rotation matrix to be used
 * @bug I believe the sum below is incorrect
 */
void Model::rotate(glm::mat4& rotationMatrix)
{
    m_RotationMatrix = rotationMatrix;
    m_ModelMatrix *= m_RotationMatrix;
}


/**
 * @brief Renders model on screen. Calls Renderable::render()
 */
void Model::render() {
    if (m_TextureVector.empty()) addTexture("res/default.jpg"); // If no texture specified, use default texture
    bindTextures();
    Renderable::render(m_IB.getCount());
}