#pragma once

#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"


class Renderable {
protected:
    virtual inline const void render() const = 0;
    const void render(const unsigned int indicesCount) const;

public:
    inline Renderable() {};
    virtual inline ~Renderable() {}

    virtual inline VertexBuffer& getVertexBuffer() = 0;
    virtual inline VertexBufferLayout& getBufferLayout() = 0;

    friend class Renderer;
};