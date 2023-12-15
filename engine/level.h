#pragma once

#include "opengl/scene.h"

class Level : public Scene {
public:
    inline Level() {}
    inline ~Level() {}

    inline virtual void update() = 0;
};