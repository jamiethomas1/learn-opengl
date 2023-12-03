#include "window.h"

#include <assert.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(const unsigned int width, const unsigned int height, const std::string title)
    : m_Width(width), m_Height(height), m_Title(title.c_str())
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
    if (m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        assert(false);
    }
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        assert(false);
    }

    glViewport(0, 0, m_Width, m_Height);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}

Window::~Window()
{
}

// Probably a temporary location for this function, can see this being expanded into its own file/class.
const void Window::processInput() const
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }
}

const void Window::update() const {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

const bool Window::isOpen() const {
    return (!glfwWindowShouldClose(m_Window));
}
