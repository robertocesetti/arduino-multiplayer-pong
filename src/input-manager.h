#pragma once

#include "gameEntities/game-entity.h"
#include "scenes/scene-manager.h"

class InputManager
{
private:
    const int HORZ = A0;
    const int VERT = A1;
    const int SEL = 2;
    SceneManager* sceneManager;

public:
    InputManager(SceneManager* sceneManager);
    ~InputManager();

    void startReading(GameEntity* gameEntities);
};
