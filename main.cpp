#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp> // for glm::perspective()

#include "engine/opengl/renderer.h"
#include "engine/opengl/window.h"
#include "engine/opengl/shader.h"
#include "engine/opengl/texture.h"

#include "sandbox/cube.h"


/**
 * TODO: Abstract matrices (may want to wait until Camera implemented) - Not going to do this until I can see a clear benefit of it
 * TODO: Implement Scene/Level class. Camera probably to be made non-static and a member of Scene/Level
*/

int main()
{
    Window::init(800, 600, "LearnOpenGL");
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
    }

    while (Window::isOpen())
    {
        Window::processInput();
        
        Renderer::clear();
        Renderer::draw();

        Window::update();
    }

    Renderer::cleanup();
    Window::cleanup();

    glfwTerminate();
    return 0;
}