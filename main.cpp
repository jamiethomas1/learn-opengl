#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp> // for glm::perspective()

#include "graphics/opengl/renderer.h"
#include "graphics/opengl/window.h"
#include "graphics/opengl/shader.h"
#include "graphics/opengl/texture.h"

#include "sandbox/cube.h"


const int WIDTH = 800;
const int HEIGHT = 600;

/**
 * DONE: Improve directory structure
 * DONE: Make everthing that can be const, const
 * DONE: Rename Entity class to Model
 * DONE: Create parent class of Entity called Renderable, contains render() method
 * DONE: Add std::vector<Renderable> to Renderer called m_RenderQueue
 * DONE: Add overload of Renderer::draw() which loops through m_RenderQueue
 * DONE: Decide whether to put glDrawElements call in draw() function or Renderable::render()
 * DONE: I need to get the data to the Model class somehow before its constructor ends
 * DONE: Finish building Cube/Model/Renderable classes to be able to provide relevant info to Renderer
 * DONE: Consider moving the VAO to the Renderer class
 * DONE: Create default shaders, and add a Shader as a field of Model class
 * DONE: Create default textures, and add a Texture as a field of Model class - Should be an array of textures
 * DONE: Work out why only one cube is showing. Are they all inside each other? If so, why are the matrices not correct?
 * DONE: Implement a way to get and set rotation of Model matrix. First attempt hasn't worked, need to try again
 * TODO: Abstract matrices (may want to wait until Camera implemented) - Not going to do this until I can see a clear benefit of it
 * TODO: Make Window static so WIDTH and HEIGHT are accessible throughout program
 * DONE: Make Renderer static so I can push Renderables to the renderer in their constructors
 * DONE: Implement an OpenGL error wrapper for all GL calls
 * DONE: Add extensive comments and make code look clear and easy to read
*/

int main()
{

    /**
     * Initialise objects
     */

    const Window *window = new Window(WIDTH, HEIGHT, "LearnOpenGL");
    Renderer::init();

    Cube* cubePositions[] = {
        new Cube(0.0f, 0.0f, 0.0f),
        new Cube(2.0f, 5.0f, -15.0f),
        new Cube(-1.5f, -2.2f, -2.5f),
        new Cube(-3.8f, -2.0f, -12.3f),
        new Cube(2.4f, -0.4f, -3.5f),
        new Cube(-1.7f, 3.0f, -7.5f),
        new Cube(1.3f, -2.0f, -2.5f),
        new Cube(1.5f, 2.0f, -2.5f),
        new Cube(1.5f, 0.2f, -1.5f),
        new Cube(-1.3f, 1.0f, -1.5f)
    };

    for (unsigned int i = 0; i < 10; i++)
    {
        float angle = 20.f * i;
        cubePositions[i]->rotate(angle, glm::vec3(1.f, 0.3f, 0.5f));
        glm::vec3 translationVector = glm::vec3(-1.f, 0.f, 0.f);
        cubePositions[i]->move(translationVector);
    }

    while (window->isOpen())
    {
        window->processInput();
        
        Renderer::clear();
        Renderer::draw();

        window->update();
    }

    Renderer::cleanup();
    delete window;

    glfwTerminate();
    return 0;
}