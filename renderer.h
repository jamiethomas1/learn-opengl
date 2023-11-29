#pragma once

#include <glad/glad.h>
#include <assert.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void clear();
    void draw(VertexArray *va, IndexBuffer *ib, Shader *sh);
};