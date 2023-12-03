#pragma once

#include "renderer.h"
#include <vector>

class IndexBuffer
{
private:
    GLuint m_ID;
    GLuint m_Count;
    std::vector<unsigned int> m_Indices;

public:
    IndexBuffer();
    IndexBuffer(const GLuint *data, const GLuint count);
    IndexBuffer(const std::vector<unsigned int> indices, const GLuint count);
    ~IndexBuffer();
    const void bind() const;
    const void unbind() const;

    const GLuint getCount() const { return m_Count; }

    void setData(const std::vector<unsigned int> indices);
};