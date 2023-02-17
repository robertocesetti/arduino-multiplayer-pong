#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "gameEntities/game-entity.h"
#include "game-engine.h"

// static ?

void xTaskGameLoop(void *params)
{
    static_cast<GameEngine *>(params)->getGameLoopHandler().update((GameEntity *)params);
}

void xTaskRender(void *params)
{
    static_cast<GameEngine *>(params)->getRenderEngine().render((GameEntity *)params);
}

void xTaskCommunication(void *param)
{
}

GameEngine::GameEngine(/* args */) : running(false), renderEngine{}, scene(SceneType::START), gameEntity{}
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::start()
{
    Serial.println("Ciao");

    if (running)
        return;

    running = true;

    // TODO: network.init()
    //setupEnvironment();

    //BaseType_t gameLoopTaskCreated = xTaskCreate(xTaskGameLoop, "Gameloop", 1024, &gameEntity, 1, &Handle_aTask);
    //BaseType_t renderTaskCreated = xTaskCreate(xTaskRender, "Rendering", 1024, &gameEntity, 1, NULL);
}

void GameEngine::setupEnvironment()
{
    int w = renderEngine.getWidth();
    int h = renderEngine.getHeight();
    gameEntity.initialize(w, h);
}

GameLoop GameEngine::getGameLoopHandler()
{
    return gameLoop;
}

RenderEngine GameEngine::getRenderEngine()
{
    return renderEngine;
}

bool GameEngine::isRunning(){
    return running;
}

void GameEngine::stop()
{
    vTaskDelete(Handle_aTask);

    running = false;
}