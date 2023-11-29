#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "texture.h"

// float vertices[] = {
//     // positions
//      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
//      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
// };

// GLuint indices[] = {
//     0, 1, 2
// };

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main()
{

    /**
     * Initialise objects
    */
    
    Window *window = new Window(800, 600, "LearnOpenGL");
    Renderer *renderer = new Renderer();
    Shader *shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    VertexArray *vao = new VertexArray();
    VertexBuffer *vbo = new VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer *ibo = new IndexBuffer(indices, 6);
    VertexBufferLayout *vbl = new VertexBufferLayout();

    Texture *crateTexture = new Texture("res/container.jpg", GL_TEXTURE0, GL_RGB); // Perhaps a separate image class so the RGBA format is stored with the image
    Texture *awesomeTexture = new Texture("res/awesomeface.png", GL_TEXTURE1, GL_RGBA);

    shader->use();
    shader->setInt("tex", 0);
    shader->setInt("tex2", 1);

    /**
        * Push vertices & add buffer to vertex array
    */

    vbl->push(GL_FLOAT, 3);
    vbl->push(GL_FLOAT, 3);
    vbl->push(GL_FLOAT, 2);

    vao->addBuffer(*vbo, *vbl);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (window->isOpen())
    {
        window->processInput();
        renderer->clear();

        float time = glfwGetTime();
        shader->setFloat("time", time);
        glm::mat4 trans = glm::mat4(1.f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));
        trans = glm::rotate(trans, time, glm::vec3(0.f, 0.f, 1.f));
        shader->setUniformMatrix4fv("transform", trans);

        crateTexture->bind();
        awesomeTexture->bind();

        renderer->draw(vao, ibo, shader);

        trans = glm::mat4(1.f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.f));
        trans = glm::scale(trans, glm::vec3(sin(time)));
        shader->setUniformMatrix4fv("transform", trans);

        renderer->draw(vao, ibo, shader);

        window->update();
    }

    delete(awesomeTexture);
    delete(crateTexture);
    delete(vbl);
    delete(ibo);
    delete(vbo);
    delete(vao);
    delete(shader);
    delete(renderer);
    delete(window);

    glfwTerminate();
    return 0;
}