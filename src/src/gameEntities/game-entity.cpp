#include "game-entity.h"
#include <Arduino.h>

GameEntity::GameEntity()
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::initialize(DisplayProperties *displayProperties)
{
    this->displayProperties = displayProperties;
}

void GameEntity::resetGame()
{
    const int space = 10;
    int width = displayProperties->width;
    int height = displayProperties->height;

    resetBall();
    paddle1.setPosition(displayProperties->topLeftX + 1 + space, (height - paddle1.getHeight()) / 2);
    paddle2.setPosition(displayProperties->topRightX - paddle2.getWidth() - space, (height - paddle2.getHeight()) / 2);
    paddle1.resetScore();
    paddle2.resetScore();
}

void GameEntity::resetBall()
{
    ball.setPosition((displayProperties->width - ball.getRadius()) / 2, (displayProperties->height - ball.getRadius()) / 2);

    float velX = START_VELOCITY_X;
    if (ball.getVelocityX() < 0)
    {
        velX *= -1;
    }
    ball.updateVelocity(velX, START_VELOCITY_Y);
}