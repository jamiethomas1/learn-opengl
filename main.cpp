#include "graphics/opengl/renderer.h"
#include "graphics/opengl/window.h"
#include "graphics/opengl/shader.h"
#include "graphics/opengl/vertexBuffer.h"
#include "graphics/opengl/indexBuffer.h"
#include "graphics/opengl/vertexArray.h"
#include "graphics/opengl/vertexBufferLayout.h"
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
 * TODO: Create default shaders, and add a Shader as a field of Model class
 * DONE: Consider moving the VAO to the Renderer class
*/

float vertices[] = {
    // positions          // textures
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3,

    4, 5, 7,
    5, 6, 7,

    8, 9, 11,
    9, 10, 11,

    12, 13, 15,
    13, 14, 15,

    16, 17, 19,
    17, 18, 19,

    20, 21, 23,
    21, 22, 23};

int main()
{

    /**
     * Initialise objects
     */

    const Window *window = new Window(WIDTH, HEIGHT, "LearnOpenGL");
    Renderer *renderer = new Renderer();
    const Shader *shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    // const VertexArray *vao = new VertexArray();
    // const VertexBuffer *vbo = new VertexBuffer(vertices, sizeof(vertices));
    // const IndexBuffer *ibo = new IndexBuffer(indices, 36);
    // VertexBufferLayout *vbl = new VertexBufferLayout();

    Cube *cube = new Cube(glm::vec3(0.f, 0.f, 0.f));
    renderer->push(cube);

    const Texture *crateTexture = new Texture("res/container.jpg", GL_TEXTURE0, GL_RGB); // Perhaps a separate image class so the RGBA format is stored with the image
    const Texture *awesomeTexture = new Texture("res/awesomeface.png", GL_TEXTURE1, GL_RGBA);

    shader->use();
    shader->setInt("tex", 0);
    shader->setInt("tex2", 1);

    /**
     * Push vertices & add buffer to vertex array
     */

    // vbl->push(GL_FLOAT, 3);
    // vbl->push(GL_FLOAT, 2);

    // vao->addBuffer(*vbo, *vbl);

    /**
     * Dealing with matrices
     */

    glm::mat4 model = glm::mat4(1.f);

    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    while (window->isOpen())
    {
        window->processInput();
        renderer->clear();

        crateTexture->bind();
        awesomeTexture->bind();

        float time = glfwGetTime();
        shader->setFloat("time", time);

        // for (unsigned int i = 0; i < 10; i++)
        // {
        //     model = glm::mat4(1.f);
        //     model = glm::translate(model, cubePositions[i]);
        //     float angle = 20.f * i;
        //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.f, 0.3f, 0.5f));

        //     shader->setUniformMatrix4fv("model", model);
        //     shader->setUniformMatrix4fv("view", view);
        //     shader->setUniformMatrix4fv("projection", projection);

        //     renderer->draw(vao, ibo, shader);
        // }
        shader->setUniformMatrix4fv("model", cube->getModelMatrix());
        shader->setUniformMatrix4fv("view", view);
        shader->setUniformMatrix4fv("projection", projection);
        renderer->draw(shader);

        window->update();
    }

    delete (awesomeTexture);
    delete (crateTexture);
    //delete (cube);
    // delete (vbl);
    // delete (ibo);
    // delete (vbo);
    // delete (vao);
    delete (shader);
    delete (renderer);
    delete (window);

    glfwTerminate();
    return 0;
}