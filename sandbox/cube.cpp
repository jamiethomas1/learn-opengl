#include "cube.h"

Cube::Cube(glm::vec3 position) : Model(position)
{
    setVertices(m_Vertices);
    setIndices(m_Indices);
}
