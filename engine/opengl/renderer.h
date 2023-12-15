#pragma once

#include <vector>

#include "scene.h"
#include "sceneCamera.h"
#include "renderable.h"
#include "vertexArray.h"
#include "shader.h"

/**
 * * Forward declaration of Renderable as Renderer needs to be included 
 * * in Renderable to be safely declared as a friend
*/
class Renderable;
class Scene;
class SceneCamera;

class Renderer {
public:
    static void init();
    static void cleanup();

    static VertexArray m_ModelVA;
    static VertexArray m_LightingVA;
    static std::vector<Renderable*> m_RenderQueue;

    static void push(Renderable* r);

    static const void clear();
    
    static const void drawScene(Scene* scene);
    static const void drawModels(std::vector<Renderable*> models, SceneCamera *camera);
    static const void drawLights(std::vector<Renderable*> lights, SceneCamera *camera);

    static float deltaTime, lastFrame;
private: 
    Renderer() {}
    ~Renderer() {}
};