#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "shader.h"

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader *shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    VertexArray *vao = new VertexArray();

    VertexBuffer *vbo = new VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer *ibo = new IndexBuffer(indices, 6);

    VertexBufferLayout *vbl = new VertexBufferLayout();
    vbl->push(GL_FLOAT, 3);
    vbl->push(GL_FLOAT, 3);
    vao->addBuffer(*vbo, *vbl);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.f) + 0.5f;
        shader->setFloat("codeColor", greenValue);

        vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glBindVertexArray(0);

    delete(vbo);
    delete(ibo);
    delete(vbl);
    delete(vao);
    delete(shader);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}