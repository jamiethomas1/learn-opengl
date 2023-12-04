#include "shader.h"

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

    // Get shader code as raw text
    const char* vShaderSource = parseShader(vertexPath);
    const char* fShaderSource = parseShader(fragmentPath);

    // Declare variables for error-checking
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete shader data from memory as both have now been linked into shader program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

/**
 * @brief Wrapper for glDeleteProgram
*/
Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

/**
 * @brief Wrapper for glUseProgram
*/
const void Shader::use() const
{
    glUseProgram(m_ID);
}

/**
 * @brief Set a boolean uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setBool(const std::string &name, const bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int) value);
}

/**
 * @brief Set an integer uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setInt(const std::string &name, const int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

/**
 * @brief Set a float uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setFloat(const std::string &name, const float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

/**
 * @brief Set a vec3 uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setVec3f(const std::string &name, const glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

/**
 * @brief Set a mat4 uniform on the shader program
 * @param name The name of the uniform
 * @param value The value of the uniform
*/
const void Shader::setMatrix4x4f(const std::string &name, const glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}