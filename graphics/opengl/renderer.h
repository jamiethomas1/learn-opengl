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
public:
    Renderer();
    ~Renderer();

    static void init();
    static void cleanup();

    static VertexArray m_VA;
    static std::vector<Renderable*> m_RenderQueue;

    static void push(Renderable* r);

    static const void clear();
    static const void draw();
};