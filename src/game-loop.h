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
    void update(GameEntity *gameEntities);
    void setDisplayProperties(DisplayProperties *displayProperties) { this->displayProperties = displayProperties; }
    void GameLoop::checkCollisionWithBoard(Entity *ball, unsigned int dimension);
    void GameLoop::checkCollisionWithPaddle(Ball* ball, Paddle *paddle);
};

