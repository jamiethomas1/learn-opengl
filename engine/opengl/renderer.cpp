#include "renderer.h"

#include <glad/glad.h>
#include "checkGLErrors.h"
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp>

#include "camera.h"
#include "window.h"


// Static variables
VertexArray Renderer::m_ModelVA;
VertexArray Renderer::m_LightingVA;
std::vector<Renderable*> Renderer::m_RenderQueue;
float Renderer::deltaTime = 0.f;
float Renderer::lastFrame = 0.f;


/**
 * @brief Initialise Renderer
*/
void Renderer::init() 
{
    GL_CALL(glEnable(GL_DEPTH_TEST));
    m_ModelVA.init();
    m_LightingVA.init();
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
    m_ModelVA.cleanup();
    m_LightingVA.cleanup();
}


/**
 * @brief Push a Renderable object to the render queue
 * @details Renderer::draw() will loop through the queue and call ->render() on each element
 * @param r Pointer to renderable object to be pushed to queue
 * @note Objects passed as arguments will be deleted by Renderer::cleanup()
*/
void Renderer::push(Renderable *r)
{

    switch (r->getType()) {
        case Renderable::Type::MODEL:
            m_ModelVA.addBuffer(r->getVertexBuffer(), r->getBufferLayout());
            break;
        case Renderable::Type::LIGHT:
            m_LightingVA.addBuffer(r->getVertexBuffer(), r->getBufferLayout());
            break;
        default:
            m_ModelVA.addBuffer(r->getVertexBuffer(), r->getBufferLayout());
            std::cerr << "No Type enum specified in derived class of Renderable. Assuming Type is Model." << std::endl;
    }

    m_RenderQueue.push_back(r); // * Might need separate render queue for lighting? Hope not
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
    // Calculate deltaTime
    float currentFrame = Window::getTime();
    Renderer::deltaTime = currentFrame - lastFrame;
    Renderer::lastFrame = currentFrame;

    // Allow camera to process input for movement & orientation
    Camera::update();

    for (Renderable *r : m_RenderQueue) {
        switch (r->getType()) {
            case Renderable::Type::MODEL:
                m_ModelVA.bind();
                break;
            case Renderable::Type::LIGHT:
                m_LightingVA.bind();
                break;
            default:
                m_ModelVA.bind();
                std::cerr << "No Type enum specified in derived class of Renderable. Assuming Type is Model." << std::endl;
        }
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)Window::width / (float)Window::height, 0.1f, 100.f);
        glm::mat4 view = Camera::viewMatrix;
        glm::mat4 mvp = projection * view * r->getModelMatrix();

        r->getShader()->use();
        r->getShader()->setMatrix4x4f("transform", mvp);
        
        r->render();
    }
}