#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "gameEntities/game-entity.h"
#include "game-engine.h"

void xTaskRender(void *params)
{
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getRenderEngine()->render(engine->getGameEntity());
}

void xTaskGameLoop(void *params)
{
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getGameLoopHandler()->update(engine->getGameEntity());
}

void xTaskCommunication(void *param)
{
}

GameEngine::GameEngine() : running(false), scene(START)
{
    RenderEngine *renderEngine = getRenderEngine();
    gameLoop.setDisplayProperties(renderEngine->getDisplayProperties());
    gameEntity.initialize(renderEngine->getDisplayProperties());
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
    createTasks();
}

void GameEngine::createTasks()
{
    BaseType_t renderTaskCreated = xTaskCreate(xTaskRender, "Rendering", 256, this, 1, NULL);
    if (renderTaskCreated == pdPASS)
    {
        Serial.println("Rendering Task created!");
    }
    else
    {
        Serial.println("Rendering Task NOT created!");
    }

    BaseType_t gameLoopTaskCreated = xTaskCreate(xTaskGameLoop, "Gameloop", 256, this, 1, NULL);
    if (gameLoopTaskCreated == pdPASS)
    {
        Serial.println("GameLoop Task created!");
    }
    else
    {
        Serial.println("GameLoop Task NOT created!");
    }
}

void GameEngine::stop()
{
    running = false;
}