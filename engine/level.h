#pragma once

#include "opengl/scene.h"
#include "levelCamera.h"

class Level : public Scene {
public:
    inline Level() : m_Camera(new LevelCamera()) {}
    inline ~Level() {}

    inline virtual void update() = 0;

    inline LevelCamera* getCamera() { return m_Camera; }

    glm::mat4 getViewMatrix() override;

protected:
    LevelCamera* m_Camera;
};