#include <Arduino.h>
#include "game-loop.h"
#include "game-task-manager.h"

static const int SKEW = 3;
static const int UPS_SET = 30;
static const int MAXBOUNCEANGLE = 75;
static const int BALL_SPEED = 1;

GameLoop::GameLoop() : resumed(false)
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::update(GameEntity *gameEntities)
{
    Ball *ball = gameEntities->getBall();
    Paddle *paddle1 = gameEntities->getPaddle1();
    Paddle *paddle2 = gameEntities->getPaddle2();
    ball->updateVelocity(1, 1);
    paddle1->updateVelocity(0, 2);
    // paddle2->updateVelocity(0, -0.2f);

    const double MS_PER_UPDATE = 1000.0 / UPS_SET;
    unsigned long current = millis();
    unsigned long previous = current;
    unsigned long lastCheck = current;
    unsigned long elapsed = 0L;
    double lag = 0.0;
    int ups = 0;

    while (true)
    {
        current = millis();
        if (resumed)
        {
            previous = current;
            resumed = false;
        }
        elapsed = current - previous;
        previous = current;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            ups++;
            if (currentScene != nullptr)
                currentScene->tick();
            lag -= MS_PER_UPDATE;
        }

        if (current - lastCheck >= 1000)
        {
            lastCheck = current;
            Serial.printf("UPS: %i\n", ups);
            ups = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void GameLoop::changeScene(Scene *scene)
{
    /*
    Serial.println(scene->getSceneType());
    Serial.println(scene->useTick());
    Serial.println("BEFORE");
    Serial.printf("Pointer address: %p", GameTaskManager::getInstance()->getGameLoopTaskHandler());
    Serial.println(eTaskGetState(GameTaskManager::getInstance()->getGameLoopTaskHandler()));
    */

    if (scene->useTick())
    {
        Serial.printf("Try to resume %s, from status %s\n", pcTaskGetName(GameTaskManager::getInstance()->tasks.gameLoopTaskHandler), STATE_NAMES[eTaskGetState(GameTaskManager::getInstance()->tasks.gameLoopTaskHandler)]);
        resumed = true;
        vTaskResume(GameTaskManager::getInstance()->tasks.gameLoopTaskHandler);
    }
    else
    {
        Serial.printf("Try to suspend %s, from status %s\n", pcTaskGetName(GameTaskManager::getInstance()->tasks.gameLoopTaskHandler), STATE_NAMES[eTaskGetState(GameTaskManager::getInstance()->tasks.gameLoopTaskHandler)]);
        vTaskSuspend(GameTaskManager::getInstance()->tasks.gameLoopTaskHandler);
    }
    // Serial.println("AFTER");
    // Serial.println(eTaskGetState(GameTaskManager::getInstance()->getGameLoopTaskHandler()));

    currentScene = scene;
}