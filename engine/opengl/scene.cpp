#include "scene.h"

#include "renderer.h"
#include "sceneCamera.h"

Scene::Scene()
    : m_Camera(new SceneCamera())
{
}

glm::mat4 Scene::getViewMatrix()
{
    return m_Camera->getViewMatrix();
}
