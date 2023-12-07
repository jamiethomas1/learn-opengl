#include "inputManager.h"

#include "window.h"

bool InputManager::isKeyDown(int key)
{
    return (bool) glfwGetKey(Window::window, key);
}

void InputManager::getMousePos(double *x, double *y)
{
    glfwGetCursorPos(Window::window, x, y);
}

void InputManager::update()
{
    glfwPollEvents();
}
