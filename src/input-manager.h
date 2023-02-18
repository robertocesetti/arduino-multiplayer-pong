#pragma once

#include "gameEntities/game-entity.h"

class InputManager
{
private:
    const int HORZ = A0;
    const int VERT = A1;
    const int SEL = 2;
public:
    InputManager();
    ~InputManager();

    void startReading(GameEntity* gameEntities);
};
