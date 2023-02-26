#pragma once

#include "../gameEntities/game-entity.h"
#include "scene.h"

class PauseScene : public Scene
{
private:
    unsigned long lastTime = 0; 
    bool drawPlayImage = true;

public:
    PauseScene();
    ~PauseScene();

    void render() override;
    void tick() override;
    bool useTick() override { return true; }
    bool renderOnce() override { return false; }
};