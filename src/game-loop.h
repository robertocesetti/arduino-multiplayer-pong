#pragma once

#include "gameEntities/game-entity.h"
#include "render-engine.h"

class GameLoop
{
private:
    DisplayProperties* displayProperties;
    void setDisplayProperties(int width, int height);

public:
    GameLoop();
    ~GameLoop();
    void setDisplayProperties(DisplayProperties* displayProperties) { this->displayProperties = displayProperties; }
    void update(GameEntity* gameEntities);
};

