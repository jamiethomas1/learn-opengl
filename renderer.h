#pragma once

#include <glad/glad.h>
#include <assert.h>

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