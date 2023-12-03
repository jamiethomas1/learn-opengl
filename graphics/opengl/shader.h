#pragma once

#include "renderer.h"
#include <iostream>

class Shader {
private:
    GLuint m_ID;

    const char* parseShader(const char *path) const;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    const void use() const;
    
    const void setBool(const std::string &name, const bool value) const;
    const void setInt(const std::string &name, const int value) const;
    const void setFloat(const std::string &name, const float value) const;

    const void setUniformMatrix4fv(const std::string &name, const glm::mat4 value) const;

    const GLuint getID() const { return m_ID; }
};
