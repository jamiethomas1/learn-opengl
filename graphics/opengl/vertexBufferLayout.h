#pragma once

#include <glad/glad.h>
#include <vector>

struct VertexBufferElement {
    const unsigned int type;
    const unsigned int count;
    const unsigned int normalized;

    static unsigned int getSizeOfType(const unsigned int type) {
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
    unsigned int m_Stride;

public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void push(const unsigned int type, const unsigned int count);

    inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
    inline const unsigned int getStride() const { return m_Stride; }
};