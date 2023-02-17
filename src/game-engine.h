#pragma once

#include <Arduino_FreeRTOS.h>
#include "gameEntities/paddle.h"
#include "gameEntities/ball.h"
#include "render-engine.h"
#include "game-loop.h"

enum SceneType { START, GAME, END };

class GameEngine
{
private:
    bool running;
    RenderEngine renderEngine;
    SceneType scene;
    TaskHandle_t Handle_aTask;
    GameEntity gameEntity;
    GameLoop gameLoop;

    void setupEnvironment();

public:
    GameEngine();
    ~GameEngine();
    void start();
    void stop();

    GameLoop getGameLoopHandler();
    RenderEngine getRenderEngine();
    GameEntity getGameEntity();
    bool isRunning();
};