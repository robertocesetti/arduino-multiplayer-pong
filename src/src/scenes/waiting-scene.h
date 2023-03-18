#pragma once

#include "scene.h"

class WaitingScene : public Scene
{
private:
    unsigned long lastTime = 0;
    bool drawPlayImage = true;

public:
    WaitingScene();
    ~WaitingScene();

    void render() override;
    bool useTick() override { return false; }
    bool renderOnce() override { return true; }
};