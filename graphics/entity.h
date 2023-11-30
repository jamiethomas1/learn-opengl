#pragma once

#include "opengl/vertexBuffer.h"
#include "opengl/indexBuffer.h"
#include "opengl/vertexBufferLayout.h"

#include <vector>

class Entity {
protected:
    const std::vector<float> m_Vertices;
    const std::vector<unsigned int> m_Indices;

    const VertexBuffer m_VB;
    const IndexBuffer m_IB;
    VertexBufferLayout m_Layout;

public:
    Entity();
    virtual inline ~Entity() {};
};