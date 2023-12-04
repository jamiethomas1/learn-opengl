#pragma once

#include <glm/glm.hpp>

#include "opengl/vertexBuffer.h"
#include "opengl/indexBuffer.h"
#include "opengl/vertexBufferLayout.h"

#include "opengl/renderable.h"

#include <vector>

class Model : public Renderable {
protected:
    glm::vec3 m_Position;

    VertexBuffer m_VB;
    IndexBuffer m_IB;
    VertexBufferLayout m_Layout;
    glm::mat4 m_ModelMatrix;

public:
    inline Model() : Model(glm::vec3(0.f, 0.f, 0.f)) {}
    Model(const glm::vec3 position);
    virtual inline ~Model() {}

    inline void setVertices(std::vector<float> vertices) { m_VB.setData(vertices); }
    inline void setIndices(std::vector<unsigned int> indices) { m_IB.setData(indices); }

    inline VertexBuffer& getVertexBuffer() override { return m_VB; }
    inline VertexBufferLayout& getBufferLayout() override { return m_Layout; }

    virtual inline const glm::vec3 getPosition() const { return m_Position; }
    virtual inline void setPosition(const glm::vec3 position) { m_Position = position; }

    virtual void modelTransform();
    virtual const glm::mat4 getModelMatrix() const { return m_ModelMatrix; }

    const void render() const override;
};