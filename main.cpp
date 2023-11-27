#include "stb_image.h"

#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"

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


    /**
     * Temporary implementation of textures
    */

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    const char *path = "res/container.jpg";
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }

    stbi_image_free(data);

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

        glBindTexture(GL_TEXTURE_2D, texture);

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