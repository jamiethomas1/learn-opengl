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
 * TODO: Implement Scene/Level class. Camera probably to be made non-static and a member of Scene/Level
 * * Passing Light position to Model shader: cube.getShader()->setVec3f(light.getPos())
 * * GameLevel will be able to parse a level file to avoid making a new class for each different GameLevel
 * TODO: Read in Cube vertices & indices from file
 * DONE: Find a new way of implementing VAOs - tutorial wants different VAOs for Models and Lights
 * TODO: In Shader setters, call this->use() at beginning of each function
 * TODO: Explore stripping OpenGL Camera class back and implementing derived versions for Engine & possibly Game levels with movement etc.
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