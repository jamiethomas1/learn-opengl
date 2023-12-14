#include "inputManager.h"

#include "window.h"


/**
 * @brief Checks if key is held down
 * @param key GLFW enum of key to check
 * @return True if key held down, false if not
 */
bool InputManager::isKeyDown(int key)
{
    return (bool) glfwGetKey(Window::window, key);
}


/**
 * @brief Stores current mouse position in given variables
 * @param x variable to store mouse xPos in
 * @param y variable to store mouse yPos in
*/
void InputManager::getMousePos(double *x, double *y)
{
    glfwGetCursorPos(Window::window, x, y);
}


/**
 * @brief Wrapper for glfwPollEvents()
*/
void InputManager::update()
{
    glfwPollEvents();
}
