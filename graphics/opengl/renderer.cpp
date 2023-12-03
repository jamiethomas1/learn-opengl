#include "renderer.h"

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

Renderer::Renderer()
    : m_VA(new VertexArray())
{
    ////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    for (auto* r : m_RenderQueue) {
        delete r;
    }
}

void Renderer::push(Renderable *r)
{
    m_VA->addBuffer(r->getVertexBuffer(), r->getBufferLayout());
    m_RenderQueue.push_back(r);
}

const void Renderer::clear() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const void Renderer::draw(const Shader *sh) const
{
    m_VA->bind(); // This will probably in future be called in the renderer's constructor (Unless/until multiple VAOs become needed)
    sh->use(); // This will be called in Model::render() once the Model class has a Shader field
    for (const Renderable *r : m_RenderQueue) {
        r->render();
    }
}

const void Renderer::draw(const VertexArray *va, const Shader *sh) const
{
    va->bind(); // This will probably in future be called in the renderer's constructor (Unless/until multiple VAOs become needed)
    sh->use(); // This will be called in Model::render() once the Model class has a Shader field
    for (const Renderable *r : m_RenderQueue) {
        r->render();
    }
}

const void Renderer::draw(const VertexArray *va, const IndexBuffer *ib, const Shader *sh) const
{
    va->bind();
    ib->bind();
    sh->use();
    
    glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, 0);
}
