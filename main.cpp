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
 * * Scene is OpenGL scope, Level and Menu will be Engine scope, and GameLevel/MainMenu/PauseMenu etc. will be Game scope
 * * Camera to be made non-static, set default LevelCamera in Level (Engine) and developer can specify GameCamera in GameLevel (Game)
 * * Renderer::renderScene(const Scene& scene) will loop through Scene objects and render them itself (so no Scene::render() needed)
 * * Renderer::renderScene will call Renderer::renderModels and Renderer::renderLights
 * * Renderables (i.e. Models or Lights) will take `*this` in their constructors (a pointer to their Scene) and will call Scene::push() instead of Renderer::push()
 * * Therefore the Scene will maintain an std::vector<Renderable*> m_RenderQueue (or other name) which will have a getter so Renderer can access it
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