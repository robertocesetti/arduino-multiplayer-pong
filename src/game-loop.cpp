#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "game-loop.h"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::update(GameEntity *gameEntities)
{
    while (true)
    {
        gameEntities->getBall()->updateVelocity(1, 0);
        gameEntities->getBall()->move();

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
