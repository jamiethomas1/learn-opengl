#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window {
public:
    static GLFWwindow *window;
    static unsigned int width, height;
    static std::string title;

    Window(const unsigned int width, const unsigned int height, const std::string title);
    ~Window() {}

    static void init(const unsigned int width, const unsigned int height, const std::string title);
    static void cleanup() {}

    static const void processInput();
    static const void update();

    static const bool isOpen();

    static inline const double getTime() { return glfwGetTime(); }
};