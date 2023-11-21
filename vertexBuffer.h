#include <glad/glad.h>

class VertexBuffer
{
    private:
        GLuint id;

    public:
        VertexBuffer(const void *data, GLuint size);
        ~VertexBuffer();
        void bind();
        void unbind();
};