#include "cube.h"


/**
 * @brief Initialises Cube object with position
 * @param position Position of Cube
 * @extends Model
 */
Cube::Cube(glm::vec3 position) : Model(position, new Shader("shaders/vCube.glsl", "shaders/fCube.glsl"))
{
    setVertices(m_Vertices);
    setIndices(m_Indices);
    addTexture("res/container.jpg");
    addTexture("res/awesomeface.png");

    m_Shader->use();
    m_Shader->setVec3f("material.ambient", glm::vec3(1.f, 0.5f, 0.31f));
    m_Shader->setVec3f("material.diffuse", glm::vec3(1.f, 0.5f, 0.31f));
    m_Shader->setVec3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_Shader->setFloat("material.shininess", 32.f);
}

void Cube::update() {
    
}