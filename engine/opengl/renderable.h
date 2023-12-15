#pragma once

#include <glm/glm.hpp>

#include "renderer.h" // includes Renderer to allow it access to render()
#include "scene.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "shader.h"


class Renderable {
protected:
    virtual inline void render() = 0;
    void render(const unsigned int indicesCount);

public:
    inline Renderable() {};
    virtual inline ~Renderable() {}

    enum class Type {
        MODEL,
        LIGHT
    };

    virtual inline void update() = 0;

    virtual inline VertexBuffer& getVertexBuffer() = 0;
    virtual inline VertexBufferLayout& getBufferLayout() = 0;
    virtual inline Shader* getShader() = 0;
    virtual inline const glm::mat4 getModelMatrix() const = 0;
    virtual inline Type getType() const = 0;

    friend class Renderer;
    friend class Scene;
};