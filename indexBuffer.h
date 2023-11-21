#include <glad/glad.h>

class IndexBuffer
{
    private:
        GLuint id;

    public:
        IndexBuffer(const GLuint *data, const GLuint count);
        ~IndexBuffer();
        void bind();
        void unbind();
};