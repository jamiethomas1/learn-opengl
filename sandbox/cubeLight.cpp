#include "cubeLight.h"

#include <glm/glm.hpp>


/**
 * @brief Initialises CubeLight object with position
 * @param position Position of CubeLight
 * @extends Model
 */
CubeLight::CubeLight(glm::vec3 position) : Light(position)
{
    setVertices(m_Vertices);
    setIndices(m_Indices);

    setScale(0.2f);
}

void CubeLight::update() {
    
}