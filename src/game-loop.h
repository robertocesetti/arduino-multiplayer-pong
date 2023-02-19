#pragma once

#include "gameEntities/game-entity.h"
#include "render-engine.h"

class GameLoop
{
private:
    DisplayProperties* displayProperties;

    void tick(Ball* ball, Paddle* paddle1, Paddle* paddle2);
    void checkCollisionWithPaddle(Ball* ball, Paddle *paddle);

public:
    GameLoop();
    ~GameLoop();
    
    void update(GameEntity *gameEntities);
    void setDisplayProperties(DisplayProperties* displayProperties) { this->displayProperties = displayProperties; }
};

