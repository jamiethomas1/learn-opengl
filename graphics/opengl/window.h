#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:
    GLFWwindow *m_Window;
    unsigned int m_Width, m_Height;
    const char* m_Title;

public:
    Window(unsigned int width, unsigned int height, std::string title);
    ~Window();

    void processInput();
    void update();

    bool isOpen();
};