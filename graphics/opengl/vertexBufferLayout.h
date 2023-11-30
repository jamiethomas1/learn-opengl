#pragma once

#include "renderer.h"
#include <vector>

struct VertexBufferElement {
    GLuint type;
    GLuint count;
    GLuint normalized;

    static GLuint getSizeOfType(GLuint type) {
        switch (type) {
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_BYTE: return sizeof(char);
            default: return -1;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    GLuint m_Stride;

public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void push(GLuint type, GLuint count);

    inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
    inline GLuint getStride() const { return m_Stride; }
};