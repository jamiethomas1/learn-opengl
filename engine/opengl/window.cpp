#include "checkGLErrors.h"
#include "window.h"

#include <assert.h>

#include "inputManager.h"


GLFWwindow *Window::window;
unsigned int Window::width, Window::height;
std::string Window::title;


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
void Window::init(const unsigned int winWidth, const unsigned int winHeight, const std::string winTitle)
{
    width = winWidth;
    height = winHeight;
    title = winTitle;

    if (!glfwInit()) {
        std::cerr << "Failed to initialise GLFW" << std::endl;
        throw std::runtime_error("Failed to initialise GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(glfwErrorCallback);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        assert(false);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        assert(false);
    }

    GL_CALL(glViewport(0, 0, width, height));
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    InputManager::init();
}


/**
 * @brief Process input into window.
*/
const void Window::processInput() // Probably a temporary location for this function, can see this being expanded into its own file/class.
{
    if (InputManager::isKeyDown(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, GLFW_TRUE);
}


/**
 * @brief Swap buffers and poll events
*/
const void Window::update() {
    glfwSwapBuffers(window);
    InputManager::update();
}


/**
 * @brief Returns true unless the user has closed the window
*/
const bool Window::isOpen() {
    return (!glfwWindowShouldClose(window));
}
