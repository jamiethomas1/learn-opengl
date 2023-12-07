#pragma once

#include <vector>

// * Including these here so I don't have to include the whole of glad.c in this header file
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406


struct VertexBufferElement {
    const unsigned int type;
    const unsigned int count;
    const unsigned int normalized;

    /**
     * @brief Get type size in bytes from type GLenum
     * @param type (GLenum) The type enum
     * @return sizeof() on fundamental type
     * @throws Returns -1 if anything other than uint, float or char requested (for now)
    */
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
    VertexBufferLayout() : m_Stride(0) {}
    ~VertexBufferLayout() {}

    void push(const unsigned int type, const unsigned int count);

    inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
    inline const unsigned int getStride() const { return m_Stride; }
};