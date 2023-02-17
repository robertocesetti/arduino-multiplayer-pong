#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "gameEntities/game-entity.h"
#include "game-engine.h"

void xTaskRender(void *parmas);

void xTaskGameLoop(void *params)
{
    static_cast<GameEngine *>(params)->getGameLoopHandler().update((GameEntity *)params);
}

void xTaskCommunication(void *param)
{
}

GameEngine::GameEngine() : running(false), scene(START)
{
    // setupEnvironment();
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
    setupEnvironment();

    BaseType_t renderTaskCreated = xTaskCreate(xTaskRender, "Rendering", 256, this, 1, NULL);
    if (renderTaskCreated == pdPASS)
    {
        Serial.println("Rendering Task created!");
    }
    else
    {
        Serial.println("Rendering Task NOT created!");
    }

    // vTaskStartScheduler();

    /*
        BaseType_t gameLoopTaskCreated = xTaskCreate(xTaskGameLoop, "Gameloop", 1024, &gameEntity, 1, &Handle_aTask);
        if (gameLoopTaskCreated == pdPASS)
        {
            Serial.println("GameLoop Task created!");
        }
        Serial.println(gameLoopTaskCreated);*/
}

void xTaskRender(void *params)
{
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getRenderEngine().render(&(engine->getGameEntity()));

    while (1)
    {
        Serial.println("xTaskRender");
        //static_cast<GameEngine *>(params)->getRenderEngine().render2();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
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

GameEntity GameEngine::getGameEntity(){
    return gameEntity;
}

bool GameEngine::isRunning()
{
    return running;
}

void GameEngine::stop()
{
    vTaskDelete(Handle_aTask);

    running = false;
}