#pragma once

#include "scene.h"

class ConnectionScene : public Scene
{
private:
    unsigned long lastTime = 0;
    bool drawPlayImage = true;

public:
    ConnectionScene();
    ~ConnectionScene();

    void render() override;
    bool useTick() override { return false; }
    bool renderOnce() override { return false; }
};