#pragma once

#include <iostream>
#include <glm/glm.hpp>

class Shader {
private:
    unsigned int m_ID;

    const char* parseShader(const char *path) const;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    const void use() const;
    
    const void setBool(const std::string &name, const bool value) const;
    const void setInt(const std::string &name, const int value) const;
    const void setFloat(const std::string &name, const float value) const;

    const void setVec3f(const std::string &name, const glm::vec3 value) const;

    const void setMatrix4x4f(const std::string &name, const glm::mat4 value) const;
};
