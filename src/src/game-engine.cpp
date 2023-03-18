#include <Arduino.h>
#include "gameEntities/game-entity.h"
#include "game-engine.h"
#include "game-task-manager.h"
#include "network-manager.h"

void xTaskRender(void *params)
{
    Serial.println(F("Starting task 'xTaskRender'"));
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getRenderEngine()->render();
}

void xTaskGameLoop(void *params)
{
    Serial.println(F("Starting task 'xTaskGameLoop'"));
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getGameLoopHandler()->update(engine->getGameEntity());
}

void xTaskInputManager(void *params)
{
    Serial.println(F("Starting task 'xTaskInputManager'"));
    GameEngine *engine = static_cast<GameEngine *>(params);
    engine->getInputManager()->startReading(engine->getGameEntity());
}

void xTaskNetwork(void *params)
{
    Serial.println(F("Starting task 'xTaskNetwork'"));

    GameEngine *engine = static_cast<GameEngine *>(params);

    while (!NetworkManager::initialize(engine->getGameEntity(), engine->getSceneManager()))
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        NetworkManager::getInstance()->setLog("Failed to init ESP-NOW, retrying in " + String(ESP_INIT_RETRY / 1000) + " seconds");
        vTaskDelay(pdMS_TO_TICKS(ESP_INIT_RETRY));
    }

    // engine->getNetworkManager()->receiveData();
    NetworkManager::getInstance()->startCommunication();
}

void xTaskStatus(void *params)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = 10000;
    Serial.println(F("Starting task 'xTaskStatus'"));
    GameTaskManager *gmt = GameTaskManager::getInstance();
    while (true)
    {
        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        Serial.print(F("\n\n------ APP STATUS ------\n"));
        gmt->printTasksStatus();
        Serial.printf("Memory heap: %i (used) / %i (total)\n", ESP.getFreeHeap(), ESP.getHeapSize());
        Serial.printf("Sketch space: %i (used) / %i (available)\n", ESP.getSketchSize(), ESP.getFreeSketchSpace());
        Serial.print(F("------------------------\n\n\n"));
        Serial.printf("\nCHIP MAC: %012llx\n", ESP.getEfuseMac());
        Serial.printf("\nCHIP MODEL: %012llx\n", ESP.getChipModel());
    }
}

GameEngine::GameEngine() : running(false),
                           sceneManager(&gameEntity, &renderEngine, &gameLoop),
                           inputManager(&sceneManager)
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

    createTasks();

    gameEntity.resetGame();
    sceneManager.changeScene(CONNECTION);
}

void GameEngine::createTasks()
{

    GameTaskManager::getInstance()->tasks.networkQueueHandler = xQueueCreate(5, sizeof(Message *));

    // Create the task for the rendering
    xTaskCreatePinnedToCore(
        xTaskRender, // Pointer to the task function
        "Render",    // Task name
        4096,        // Stack size in words
        this,        // Task parameter
        1,           // Task priority
        &GameTaskManager::getInstance()->tasks.renderTaskHandler,
        1);

    // Serial.println(eTaskGetState(GameTaskManager::getInstance()->getRenderTaskHandler()));

    // Create the task for input management
    xTaskCreatePinnedToCore(
        xTaskInputManager, // Pointer to the task function
        "InputMgr",        // Task name
        4096,              // Stack size in words
        this,              // Task parameter
        1,                 // Task priority
        &GameTaskManager::getInstance()->tasks.inputTaskHandler,
        1);

    // Create the task for the game loop
    xTaskCreatePinnedToCore(
        xTaskGameLoop, // Pointer to the task function
        "GameLoop",    // Task name
        4096,          // Stack size in words
        this,          // Task parameter
        1,             // Task priority => was 2
        &GameTaskManager::getInstance()->tasks.gameLoopTaskHandler,
        1);

    // Create the task for the network loop
    xTaskCreatePinnedToCore(
        xTaskNetwork, // Pointer to the task function
        "NetLoop",    // Task name
        4096,         // Stack size in words
        this,         // Task parameter
        1,            // Task priority
        &GameTaskManager::getInstance()->tasks.networkTaskHandler,
        0);

    // Create the task for printing the status
    xTaskCreatePinnedToCore(
        xTaskStatus, // Pointer to the task function
        "StatLoop",  // Task name
        4096,        // Stack size in words
        this,        // Task parameter
        1,           // Task priority
        &GameTaskManager::getInstance()->tasks.statusTaskHandler,
        1);
}

void GameEngine::stop()
{
    running = false;
}