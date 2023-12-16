#include "renderer.h"

#include <glad/glad.h>
#include "checkGLErrors.h"
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp>

//#include "camera.h"
#include "window.h"


// Static variables
VertexArray Renderer::m_ModelVA;
VertexArray Renderer::m_LightingVA;
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
}


/**
 * @brief Deletes Renderables in render queue and runs cleanup on VertexArray & Camera
*/
void Renderer::cleanup() 
{
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
}


/**
 * @brief Clears frame for next render
*/
const void Renderer::clear()
{
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}


const void Renderer::drawScene(Scene *scene)
{
    // Calculate deltaTime
    float currentFrame = Window::getTime();
    Renderer::deltaTime = currentFrame - lastFrame;
    Renderer::lastFrame = currentFrame;

    drawModels(scene->getModels(), scene);
    drawLights(scene->getLights(), scene);
}

const void Renderer::drawModels(std::vector<Renderable *> models, Scene *scene)
{
    m_ModelVA.bind();
    for (auto& model : models) {
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)Window::width / (float)Window::height, 0.1f, 100.f);
        glm::mat4 view = scene->getViewMatrix();
        glm::mat4 mvp = projection * view * model->getModelMatrix();

        model->getShader()->use();
        model->getShader()->setMatrix4x4f("transform", mvp);
        
        model->render();
    }
}

const void Renderer::drawLights(std::vector<Renderable *> lights, Scene *scene)
{
    m_LightingVA.bind();
    for (auto& light : lights) {
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)Window::width / (float)Window::height, 0.1f, 100.f);
        glm::mat4 view = scene->getViewMatrix();
        glm::mat4 mvp = projection * view * light->getModelMatrix();

        light->getShader()->use();
        light->getShader()->setMatrix4x4f("transform", mvp);
        
        light->render();
    }
}
