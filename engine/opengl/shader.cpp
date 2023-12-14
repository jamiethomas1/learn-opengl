#include "shader.h"
#include <glad/glad.h>
#include "checkGLErrors.h"
#include <glm/gtc/type_ptr.hpp>

#include <fstream>


/**
 * @brief Read shader files into program
 * @param path Path of shader file
 * @return Raw text string of shader code
*/
const char* Shader::parseShader(const char *path) const {

    /* Shader file reading */
    FILE* shaderFile = fopen(path, "r");
    int fileSize = 0;
    char* shaderSource = NULL;

    // Getting file size
    fseek(shaderFile, 0, SEEK_END);
    fileSize = ftell(shaderFile);
    rewind(shaderFile);

    // Reading from file
    shaderSource = (char*)malloc(sizeof(char) * (fileSize + 1));
    fread(shaderSource, sizeof(char), fileSize, shaderFile);
    shaderSource[fileSize] = '\0';
    fclose(shaderFile);

    return shaderSource;
}


/**
 * @brief Generates shader program from vertex & fragment shader files. 
 * Paths are relative to containing folder of executable.
 * @param vertexPath Vertex shader path
 * @param fragmentPath Fragment shader path
 * @return Linked shader program object
*/
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::ifstream vPath(vertexPath), fPath(fragmentPath);
    if (!vPath.good()) {
        vertexPath = "shaders/vDefaultModel.glsl";
        std::cerr << "Invalid vertex shader path! Using default model shader." << std::endl;
    }
    if (!fPath.good()) {
        fragmentPath = "shaders/fDefaultModel.glsl";
        std::cerr << "Invalid fragment shader path! Using default model shader." << std::endl;
    }

    // Get shader code as raw text
    const char* vShaderSource = parseShader(vertexPath);
    const char* fShaderSource = parseShader(fragmentPath);

    // Declare variables for error-checking
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex shader
    vertex = GL_CALL(glCreateShader(GL_VERTEX_SHADER));
    GL_CALL(glShaderSource(vertex, 1, &vShaderSource, NULL));
    GL_CALL(glCompileShader(vertex));
    GL_CALL(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if (!success) {
        GL_CALL(glGetShaderInfoLog(vertex, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    fragment = GL_CALL(glCreateShader(GL_FRAGMENT_SHADER));
    GL_CALL(glShaderSource(fragment, 1, &fShaderSource, NULL));
    GL_CALL(glCompileShader(fragment));
    GL_CALL(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if (!success) {
        GL_CALL(glGetShaderInfoLog(fragment, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader program
    m_ID = GL_CALL(glCreateProgram());
    GL_CALL(glAttachShader(m_ID, vertex));
    GL_CALL(glAttachShader(m_ID, fragment));
    GL_CALL(glLinkProgram(m_ID));
    GL_CALL(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));
    if (!success) {
        GL_CALL(glGetProgramInfoLog(m_ID, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete shader data from memory as both have now been linked into shader program
    GL_CALL(glDeleteShader(vertex));
    GL_CALL(glDeleteShader(fragment));
}


/**
 * @brief Wrapper for glDeleteProgram
*/
Shader::~Shader()
{
    GL_CALL(glDeleteProgram(m_ID));
}


/**
 * @brief Wrapper for glUseProgram
*/
const void Shader::use() const
{
    GL_CALL(glUseProgram(m_ID));
}


/**
 * @brief Set a boolean uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setBool(const std::string &name, const bool value) const
{
    GL_CALL(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int) value));
}


/**
 * @brief Set an integer uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setInt(const std::string &name, const int value) const
{
    GL_CALL(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value));
}


/**
 * @brief Set a float uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setFloat(const std::string &name, const float value) const
{
    GL_CALL(glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value));
}


/**
 * @brief Set a vec3 uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setVec3f(const std::string &name, const glm::vec3 value) const
{
    GL_CALL(glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value)));
}


/**
 * @brief Set a mat4 uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setMatrix4x4f(const std::string &name, const glm::mat4 value) const
{
    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)));
}