#pragma once

#include "scene.h"

class PauseScene : public Scene
{
private:
    /* data */
public:
    PauseScene(/* args */);
    ~PauseScene();

    void render() override;
};