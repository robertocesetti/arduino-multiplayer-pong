#pragma once

// #include <Arduino_FreeRTOS.h>
#include "gameEntities/paddle.h"
#include "gameEntities/ball.h"
#include "render-engine.h"
#include "game-loop.h"
#include "input-manager.h"
#include "network-manager.h"
#include "scenes/scene-manager.h"

class GameEngine
{
private:
    bool running;
    RenderEngine renderEngine;
    GameEntity gameEntity;
    GameLoop gameLoop;
    InputManager inputManager;
    SceneManager sceneManager;

    void createTasks();

public:
    GameEngine();
    ~GameEngine();

    void start();
    void stop();

    bool isRunning() { return running; }
    GameLoop *getGameLoopHandler() { return &gameLoop; }
    RenderEngine *getRenderEngine() { return &renderEngine; }
    GameEntity *getGameEntity() { return &gameEntity; }
    InputManager *getInputManager() { return &inputManager; }
    SceneManager *getSceneManager() { return &sceneManager; }
};