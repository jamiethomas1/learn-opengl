#pragma once

#include <vector>

class IndexBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_Count;
    std::vector<unsigned int> m_Indices;

public:
    IndexBuffer();
    ~IndexBuffer();
    
    const void bind() const;
    const void unbind() const;

    const unsigned int getCount() const { return m_Count; }

    void setData(const std::vector<unsigned int> indices);
};