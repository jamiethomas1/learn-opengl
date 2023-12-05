#include "renderer.h"

#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp>

const int WIDTH = 800, HEIGHT = 600; // ! This is a very temporary solution, the proper fix is likely to make the Window class static
// * Another solution might be to make a Matrix class, include Window, and make Matrix a friend class to Window.


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
 * @note Objects passed as arguments will be deleted by the Renderer's destructor
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
*/
const void Renderer::draw()
{
    m_VA->bind(); // This will probably in future be called in the renderer's constructor (Unless/until multiple VAOs become needed)
    for (Renderable *r : m_RenderQueue) {
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f));
        glm::mat4 mvp = projection * view * r->getModelMatrix();

        r->getShader().use();
        r->getShader().setMatrix4x4f("transform", mvp);
        
        r->render();
        
        // if (!m_RenderQueue.empty()) {
        //     m_RenderQueue.erase(m_RenderQueue.begin());
        // }
    }
}
