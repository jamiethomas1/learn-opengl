#include <iostream>
#include <glad/glad.h>

// Check for OpenGL errors and print them
void checkGLErrors(const char* location) {
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error (" << location << "): " << error << std::endl;
        error = glGetError();
    }
}