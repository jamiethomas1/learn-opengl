#include "checkGLErrors.h"
#include "window.h"

#include <assert.h>


/**
 * @brief Changes viewport size when window is resized
 * @param window Window to be resized
 * @param width New width of viewport
 * @param height New height of viewport
*/
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    GL_CALL(glViewport(0, 0, width, height));
}


void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}


/**
 * @brief Create window and set to current context
 * @param width Width of viewport
 * @param height Height of viewport
 * @param title Name of window
*/
Window::Window(const unsigned int width, const unsigned int height, const std::string title)
    : m_Width(width), m_Height(height), m_Title(title.c_str())
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialise GLFW" << std::endl;
        throw std::runtime_error("Failed to initialise GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(glfwErrorCallback);

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

    GL_CALL(glViewport(0, 0, m_Width, m_Height));
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}


/**
 * @brief Process input into window.
*/
const void Window::processInput() const // Probably a temporary location for this function, can see this being expanded into its own file/class.
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }
}


/**
 * @brief Swap buffers and poll events
*/
const void Window::update() const {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}


/**
 * @brief Returns true unless the user has closed the window
*/
const bool Window::isOpen() const {
    return (!glfwWindowShouldClose(m_Window));
}
