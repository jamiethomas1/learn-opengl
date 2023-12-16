#pragma once

#include <vector>

#include <glm/glm.hpp>

class Renderable;
class SceneCamera;

class Scene {
public:
    Scene();
    ~Scene() {}

    inline virtual void update() = 0;

    inline const std::vector<Renderable*> getModels() { return m_Models; }
    inline const std::vector<Renderable*> getLights() { return m_Lights; }
    inline virtual glm::mat4 getViewMatrix() = 0;

protected:
    std::vector<Renderable*> m_Models;
    std::vector<Renderable*> m_Lights;
};