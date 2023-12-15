#pragma once

#include "../engine/level.h"

class ManyCubesLevel : public Level {
public:
    ManyCubesLevel();
    ~ManyCubesLevel();

    void update() override;
};