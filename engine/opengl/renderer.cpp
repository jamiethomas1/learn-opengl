#include "renderer.h"

#include <glad/glad.h>
#include "checkGLErrors.h"
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp>

#include "window.h"


VertexArray Renderer::m_VA;
std::vector<Renderable*> Renderer::m_RenderQueue;


/**
 * @brief Central Renderer class
*/
void Renderer::init() 
{
    GL_CALL(glEnable(GL_DEPTH_TEST));
    m_VA.init();
}


/**
 * @brief Deletes Renderables in render queue and runs cleanup on VertexArray
*/
void Renderer::cleanup() 
{
    for (auto* r : m_RenderQueue) {
        delete r;
    }
    m_VA.cleanup();
}


/**
 * @brief Push a Renderable object to the render queue
 * @details Renderer::draw() will loop through the queue and call ->render() on each element
 * @param r Pointer to renderable object to be pushed to queue
 * @note Objects passed as arguments will be deleted by the Renderer's destructor
*/
void Renderer::push(Renderable *r)
{
    m_VA.addBuffer(r->getVertexBuffer(), r->getBufferLayout());
    m_RenderQueue.push_back(r);
}


/**
 * @brief Clears frame for next render
*/
const void Renderer::clear()
{
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}


/**
 * @brief Calls ->render() on each Renderable in render queue
*/
const void Renderer::draw()
{
    m_VA.bind(); // This will probably in future be called in the renderer's constructor (Unless/until multiple VAOs become needed)

    glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 3.f);
    glm::vec3 cameraTarget = glm::vec3(0.f);
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
    
    const float radius = 10.f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    
    glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.f, camZ), cameraTarget, up);

    for (Renderable *r : m_RenderQueue) {
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)Window::width / (float)Window::height, 0.1f, 100.f);
        //glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f));
        glm::mat4 mvp = projection * view * r->getModelMatrix();

        r->getShader().use();
        r->getShader().setMatrix4x4f("transform", mvp);
        
        r->render();
        
        // if (!m_RenderQueue.empty()) {
        //     m_RenderQueue.erase(m_RenderQueue.begin());
        // }
    }
}