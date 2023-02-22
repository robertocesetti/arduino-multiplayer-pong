#pragma once

#include <Arduino_FreeRTOS.h>
#include "gameEntities/paddle.h"
#include "gameEntities/ball.h"
#include "render-engine.h"
#include "game-loop.h"
#include "input-manager.h"

const static int SCENE_NUMBER = 1; 

class GameEngine
{
private:
    bool running;
    Scene* scenes[SCENE_NUMBER];
    RenderEngine renderEngine;
    GameEntity gameEntity;
    GameLoop gameLoop;
    InputManager inputManager;

    void createScenes();
    void createTasks();

public:
    GameEngine();
    ~GameEngine();
    void start();
    void stop();
    
    bool isRunning(){return running;}
    GameLoop* getGameLoopHandler(){return &gameLoop;}
    RenderEngine* getRenderEngine(){return &renderEngine;}
    GameEntity* getGameEntity(){return &gameEntity;}
    InputManager* getInputManager(){return &inputManager;}
    void changeScene(SceneType sceneType);
};