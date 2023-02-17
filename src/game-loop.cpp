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
    Ball *ball = gameEntities->getBall();
    ball->updateVelocity(1, 0);

    while (true)
    {
        ball->move();

        // Check for collisions with the top and bottom of the screen
        if (ball->getPositionY() <= displayProperties->bottomLeftY || ball->getPositionY() > displayProperties->topLeftY)
        {
            ball->reverseVelocityY();
        }

        // Check for collisions with the left and right of the screen
        if (ball->getPositionX() <= displayProperties->topLeftX || ball->getPositionX() > displayProperties->topRightX)
        {
            ball->reverseVelocityX();
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
