#include "renderer.h"

class VertexArray {
private:
    GLuint id;

public:
    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();
};