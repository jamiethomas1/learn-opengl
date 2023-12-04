#include "renderer.h"

#include <glad/glad.h>


/**
 * @brief Central Renderer class
*/
Renderer::Renderer()
    : m_VA(new VertexArray())
{
    glEnable(GL_DEPTH_TEST);
}


/**
 * @brief Deletes VertexArray and Renderables in render queue
*/
Renderer::~Renderer()
{
    for (auto* r : m_RenderQueue) {
        delete r;
    }
    delete m_VA;
}


/**
 * @brief Push a Renderable object to the render queue
 * @details Renderer::draw() will loop through the queue and call ->render() on each element
 * @param r Pointer to renderable object to be pushed to queue
*/
void Renderer::push(Renderable *r)
{
    m_VA->addBuffer(r->getVertexBuffer(), r->getBufferLayout());
    m_RenderQueue.push_back(r);
}


/**
 * @brief Clears frame for next render
*/
const void Renderer::clear() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/**
 * @brief Calls ->render() on each Renderable in render queue
 * @param sh Pointer to shader program
*/
const void Renderer::draw(const Shader *sh) const
{
    m_VA->bind(); // This will probably in future be called in the renderer's constructor (Unless/until multiple VAOs become needed)
    sh->use(); // This will be called in Model::render() once the Model class has a Shader field
    for (const Renderable *r : m_RenderQueue) {
        r->render();
    }
}
