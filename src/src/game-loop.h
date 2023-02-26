#pragma once

#include "gameEntities/game-entity.h"
#include "render-engine.h"

class GameLoop
{
private:
    DisplayProperties *displayProperties;
    Scene *currentScene;
    bool resumed;

    void tick(Ball *ball, Paddle *paddle1, Paddle *paddle2);
    void moveUsingAI(Paddle *paddle, Ball *ball, bool godMode = false);

public:
    GameLoop();
    ~GameLoop();

    void update(GameEntity *gameEntities);
    void setDisplayProperties(DisplayProperties *displayProperties) { this->displayProperties = displayProperties; }
    void changeScene(Scene *scene);
};
