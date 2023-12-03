#pragma once

#include <glad/glad.h>
#include <assert.h>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "renderable.h"
#include "vertexArray.h"

class VertexArray;
class IndexBuffer;
class Shader;
class Renderable;

class Renderer {
private:
    std::vector<const Renderable*> m_RenderQueue;
    VertexArray *m_VA;

public:
    Renderer();
    ~Renderer();

    void push(Renderable* r);

    const void clear() const;
    const void draw(const Shader *sh) const;
    const void draw(const VertexArray *va, const Shader *sh) const;
    const void draw(const VertexArray *va, const IndexBuffer *ib, const Shader *sh) const;
};