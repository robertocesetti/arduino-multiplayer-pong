#pragma once

#include "gameEntities/game-entity.h"
#include "scenes/scene-manager.h"

class InputManager
{
private:
    const int HORZ = GPIO_NUM_34;
    const int VERT = GPIO_NUM_35;
    const int SEL = GPIO_NUM_18;
    SceneManager* sceneManager;

public:
    InputManager(SceneManager* sceneManager);
    ~InputManager();

    void startReading(GameEntity* gameEntities);
};
