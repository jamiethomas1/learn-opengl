#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:
    GLFWwindow *m_Window;
    const unsigned int m_Width, m_Height;
    const char* m_Title;

public:
    Window(const unsigned int width, const unsigned int height, const std::string title);
    ~Window();

    const void processInput() const;
    const void update() const;

    const bool isOpen() const;
};