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

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window->update();
    }

    delete(vbo);
    delete(ibo);
    delete(vbl);
    delete(vao);
    delete(shader);
    delete(window);

    glfwTerminate();
    return 0;
}