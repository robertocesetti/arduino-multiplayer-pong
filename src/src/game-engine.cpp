#include <STM32FreeRTOS.h>
#include <Arduino.h>
#include <FreeRTOSConfig.h>
#include "gameEntities/game-entity.h"
#include "game-engine.h"

/*
static StackType_t renderTaskStack[256];
static StackType_t gameLoopTaskStack[256];
static StackType_t inputManagerTaskStack[128];

static StaticTask_t renderTaskBuffer;
static StaticTask_t gameLoopTaskBuffer;
static StaticTask_t inputManagerTaskBuffer;
*/

static

    void
    xTaskRender(void *params)
{
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getRenderEngine()->render();
}

void xTaskGameLoop(void *params)
{
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getGameLoopHandler()->update(engine->getGameEntity());
}

void xTaskInputManager(void *params)
{
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getInputManager()->startReading(engine->getGameEntity());
}

void xTaskCommunication(void *params)
{
}

GameEngine::GameEngine() : running(false), sceneManager(&gameEntity, &renderEngine), inputManager(&sceneManager)
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
    if (running)
        return;

    running = true;

    sceneManager.changeScene(START);
    // TODO: network.init()
    createTasks();
}

void GameEngine::createTasks()
{
    // Create the task for the rendering
    xTaskCreate(
        xTaskRender, // Pointer to the task function
        "Render",    // Task name
        256,         // Stack size in words
        this,        // Task parameter
        1,           // Task priority
        NULL);

    // Create the task for the game loop
    xTaskCreate(
        xTaskGameLoop, // Pointer to the task function
        "GameLoop",    // Task name
        256,           // Stack size in words
        this,          // Task parameter
        1,             // Task priorit
        NULL);

    // Create the task for input management
    xTaskCreate(
        xTaskInputManager, // Pointer to the task function
        "InputMgr",        // Task name
        128,               // Stack size in words
        this,              // Task parameter
        1,                 // Task priority
        NULL);
}

void GameEngine::stop()
{
    running = false;
}