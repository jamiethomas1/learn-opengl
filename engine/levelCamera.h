#pragma once

#include "opengl/sceneCamera.h"

class LevelCamera : public SceneCamera {
public:
    inline LevelCamera() {}
    inline ~LevelCamera() {}

    void update();
};