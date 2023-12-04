#include "cube.h"


/**
 * @brief Initialises Cube object with position
 * @param position Position of Cube
 * @extends Model
 */
Cube::Cube(glm::vec3 position) : Model(position)
{
    setVertices(m_Vertices);
    setIndices(m_Indices);
}
