#pragma once

#include "../gameEntities/game-entity.h"
#include "scene.h"

class PauseScene : public Scene
{
private:
    GameEntity *gameEntities;

public:
    PauseScene(GameEntity *gameEntities);
    ~PauseScene();

    void render() override;
};