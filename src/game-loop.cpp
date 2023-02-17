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
    Paddle *paddle1 = gameEntities->getPaddle1();
    Paddle *paddle2 = gameEntities->getPaddle2();
    ball->updateVelocity(1, 0);

    int ups = 0;
    unsigned long lastTime = millis();

    while (true)
    {
        ups++;
        if (millis() > lastTime + 1000)
        {
            Serial.print("UPS: ");
            Serial.println(ups);
            lastTime = millis();
            ups = 0;
        }

        ball->move();

        checkCollisionWithBoard(ball);
        checkCollisionWithPaddle(ball, paddle1);
        checkCollisionWithPaddle(ball, paddle2);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void GameLoop::checkCollisionWithBoard(Ball *ball)
{
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
}

void GameLoop::checkCollisionWithPaddle(Ball *ball, Paddle *paddle)
{
    // Checks for the collisions with the paddle

    if((ball->getPositionX() + ball->getRadius() > paddle->getPositionX() && ball->getPositionX() - ball->getRadius() < paddle->getPositionX() + paddle->getWidth())
        && ball->getPositionY() > paddle->getPositionY() && ball->getPositionY() < (paddle->getPositionY() + paddle->getHeight())){
        ball->reverseVelocityX();
        ball->reverseVelocityY();
    }
}
