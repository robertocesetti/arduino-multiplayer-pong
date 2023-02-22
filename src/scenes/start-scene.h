#pragma once

#include "scene.h"

class StartScene : public Scene
{
private:
    /* data */
public:
    StartScene();
    ~StartScene();

    void render() override;
};
