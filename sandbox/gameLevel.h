#pragma once

#include "../engine/level.h"

class GameLevel : public Level {
public:
    GameLevel();
    ~GameLevel();

    void update() override;
};