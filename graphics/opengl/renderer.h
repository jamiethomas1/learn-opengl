#pragma once

#include <vector>

#include "renderable.h"
#include "vertexArray.h"
#include "shader.h"

/**
 * * Forward declaration of Renderable as Renderer needs to be included 
 * * in Renderable to be safely declared as a friend
*/
class Renderable;

class Renderer {
private:
    std::vector<Renderable*> m_RenderQueue;
    VertexArray *m_VA;

public:
    Renderer();
    ~Renderer();

    void push(Renderable* r);

    const void clear() const;
    const void draw();
};