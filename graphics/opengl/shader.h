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

    void use();
    
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

    void setUniformMatrix4fv(const std::string &name, glm::mat4 value);

    const GLuint getID() const { return m_ID; }
};
