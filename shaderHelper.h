#pragma once

#include <iostream>

char* parseShader(const char *path) {
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