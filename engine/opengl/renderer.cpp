#include "renderer.h"

#include <glad/glad.h>
#include "checkGLErrors.h"
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp>

#include "camera.h"
#include "window.h"


// Static variables
VertexArray Renderer::m_VA;
std::vector<Renderable*> Renderer::m_RenderQueue;
float Renderer::deltaTime = 0.f;
float Renderer::lastFrame = 0.f;


/**
 * @brief Initialise Renderer
*/
void Renderer::init() 
{
    GL_CALL(glEnable(GL_DEPTH_TEST));
    m_VA.init();
    Camera::init();
}


/**
 * @brief Deletes Renderables in render queue and runs cleanup on VertexArray & Camera
*/
void Renderer::cleanup() 
{
    for (auto* r : m_RenderQueue) {
        delete r;
    }
    Camera::cleanup();
    m_VA.cleanup();
}


/**
 * @brief Push a Renderable object to the render queue
 * @details Renderer::draw() will loop through the queue and call ->render() on each element
 * @param r Pointer to renderable object to be pushed to queue
 * @note Objects passed as arguments will be deleted by Renderer::cleanup()
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

    // Calculate deltaTime
    float currentFrame = Window::getTime();
    Renderer::deltaTime = currentFrame - lastFrame;
    Renderer::lastFrame = currentFrame;

    // Allow camera to process input for movement & orientation
    Camera::update();

    for (Renderable *r : m_RenderQueue) {
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)Window::width / (float)Window::height, 0.1f, 100.f);
        //glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f));
        glm::mat4 view = Camera::viewMatrix;
        glm::mat4 mvp = projection * view * r->getModelMatrix();

        r->getShader().use();
        r->getShader().setMatrix4x4f("transform", mvp);
        
        r->render();
    }
}