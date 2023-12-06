#pragma once

#include <iostream>
#include <glad/glad.h>

#define GL_CALL(func) \
    func; \
    checkGLError(__FILE__, __LINE__)


/**
 * @brief Check for OpenGL errors and print them
 * @param file File error occurs in
 * @param line Line error occurs on
 */
inline void checkGLError(const char* file, int line) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error in " << file << " at line " << line << ": ";
        switch (error) {
            case GL_INVALID_ENUM:
                std::cerr << "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL_INVALID_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL_OUT_OF_MEMORY";
                break;
            // Add more cases as needed
            default:
                std::cerr << "Unknown error code: " << error;
                break;
        }
        std::cerr << std::endl;
    }
}