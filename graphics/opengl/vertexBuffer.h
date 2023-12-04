#pragma once

#include <vector>

class VertexBuffer
{
private:
    unsigned int m_ID;
    std::vector<float> m_Vertices;

public:
    VertexBuffer();
    ~VertexBuffer();

    const void bind() const;
    const void unbind() const;

    void setData(std::vector<float> vertices);
};