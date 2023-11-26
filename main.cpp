#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"

// float vertices[] = {
//      0.5f,  0.5f, 0.0f, // top right
//      0.5f, -0.5f, 0.0f, // bottom right
//     -0.5f, -0.5f, 0.0f, // bottom left
//     -0.5f,  0.5f, 0.0f  // top left
// };

// GLuint indices[] = {
//     0, 1, 3,    // first triangle
//     1, 2, 3     // second triangle
// };

float vertices[] = {
    // positions
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
};

GLuint indices[] = {
    0, 1, 2
};

int main()
{
    Window *window = new Window(800, 600, "LearnOpenGL");

    Renderer *renderer = new Renderer();

    Shader *shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    VertexArray *vao = new VertexArray();

    VertexBuffer *vbo = new VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer *ibo = new IndexBuffer(indices, 6);

    VertexBufferLayout *vbl = new VertexBufferLayout();
    vbl->push(GL_FLOAT, 3);
    vbl->push(GL_FLOAT, 3);
    vao->addBuffer(*vbo, *vbl);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (window->isOpen())
    {
        window->processInput();
        renderer->clear();
        
        renderer->draw(vao, ibo, shader);

        window->update();
    }

    delete(vbo);
    delete(ibo);
    delete(vbl);
    delete(vao);
    delete(shader);
    delete(window);
    delete(renderer);

    glfwTerminate();
    return 0;
}