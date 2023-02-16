#include <Arduino_FreeRTOS.h>
#include "gameEntities/game-entity.h"
#include "game-engine.h"

GameEngine::GameEngine(/* args */) : running(false), renderEngine{}, scene(SceneType::START), gameEntity{}
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::start()
{
    if (running)
        return;

    running = true;

    // network.init()
    setupEnvironment();

    xTaskCreate(xTaskGameLoop, "Gameloop", 128, &gameEntity, 1, &Handle_aTask);
    xTaskCreate(xTaskRender, "Rendering", 128, &gameEntity, 1, nullptr);
}

void GameEngine::setupEnvironment()
{
    int w = renderEngine.getWidth();
    int h = renderEngine.getHeight();
    gameEntity.initialize(w, h);
}

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

GameLoop GameEngine::getGameLoopHandler()
{
    return gameLoop;
}

RenderEngine GameEngine::getRenderEngine()
{
    return renderEngine;
}

void GameEngine::stop()
{
    vTaskDelete(Handle_aTask);

    running = false;
}