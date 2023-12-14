#pragma once

#include <glm/glm.hpp>

#include "opengl/vertexBuffer.h"
#include "opengl/indexBuffer.h"
#include "opengl/vertexBufferLayout.h"
#include "opengl/shader.h"

#include "opengl/renderable.h"

#include <vector>


class Light : public Renderable {
protected:
    glm::vec3 m_Position;
    glm::mat4 m_RotationMatrix;

    VertexBuffer m_VB;
    IndexBuffer m_IB;
    VertexBufferLayout m_Layout;
    Shader *m_Shader;
    glm::mat4 m_ModelMatrix;

public:
    inline Light() : Light(glm::vec3(0.f, 0.f, 0.f)) {}
    Light(const glm::vec3 position);
    virtual inline ~Light() {}

    inline void setVertices(std::vector<float> vertices) { m_VB.setData(vertices); }
    inline void setIndices(std::vector<unsigned int> indices) { m_IB.setData(indices); }

    inline VertexBuffer& getVertexBuffer() override { return m_VB; }
    inline VertexBufferLayout& getBufferLayout() override { return m_Layout; }
    inline Shader* getShader() override { return m_Shader; }

    inline Type getType() const override { return Type::LIGHT; }

    inline const glm::vec3 getPosition() const { return m_Position; }
    void setPosition(const glm::vec3 position);

    void setRotation(const float angle, const glm::vec3 axis);
    void setRotation(glm::mat4& rotationMatrix);

    void setScale(const float scaleFactor);

    void move(glm::vec3& movement);
    void move(glm::mat4& translationMatrix);

    void rotate(float angle, const glm::vec3& axis);
    void rotate(glm::mat4& rotationMatrix);

    virtual const glm::mat4 getModelMatrix() const override { return m_ModelMatrix; }

    void render() override;
};