#include "renderer.h"

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

Renderer::Renderer()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
}

void Renderer::clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(VertexArray *va, IndexBuffer *ib, Shader *sh)
{
    va->bind();
    ib->bind();
    sh->use();
    
    glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, 0);
}
