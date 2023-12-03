#include "cube.h"

Cube::Cube()
{
    setVertices(m_Vertices);
    setIndices(m_Indices);
}

Cube::Cube(glm::vec3 position) : Model(position)
{
    setVertices(m_Vertices);
    setIndices(m_Indices);
}
