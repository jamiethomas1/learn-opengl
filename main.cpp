#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // for glm::translate()
#include <glm/ext/matrix_clip_space.hpp> // for glm::perspective()

#include "engine/opengl/renderer.h"
#include "engine/opengl/window.h"
#include "engine/opengl/shader.h"
#include "engine/opengl/texture.h"

#include "sandbox/gameLevel.h"
#include "sandbox/manyCubesLevel.h"


/**
 * DONE: Give Light class an m_Color member and in GameLevel, do cube->getShader()->setVec3f("lightColor", cubeLight->getColor())
 * TODO: Make a Material class, and make a Shader method that parses the Material and sets up the Model's Material GLSL struct
 * TODO: Read in Cube vertices & indices from file
 * TODO: Change controls slightly to be like Minecraft flying
 * TODO: Build levels in their own files, read into GameLevel class
 * TODO: Abstract matrices (may want to wait until Camera implemented) - Not going to do this until I can see a clear benefit of it
*/


int main()
{
    Window::init(800, 600, "LearnOpenGL");
    Renderer::init();

    GameLevel *level = new GameLevel();
    //ManyCubesLevel *level = new ManyCubesLevel();

    while (Window::isOpen())
    {
        Window::processInput();
        
        level->update();
        Renderer::clear();
        Renderer::drawScene(level);

        Window::update();
    }

    Renderer::cleanup();
    Window::cleanup();

    glfwTerminate();
    return 0;
}