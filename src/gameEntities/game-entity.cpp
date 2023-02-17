#include "game-entity.h"

GameEntity::GameEntity()
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::initialize(DisplayProperties *displayProperties)
{
    const int space = 10;
    int width = displayProperties->width;
    int height = displayProperties->height;
    ball.setPosition((width - ball.getRadius()) / 2, (height - ball.getRadius()) / 2);
    paddle1.setPosition(displayProperties->topLeftX + 1 + space, (height - paddle1.getHeight()) / 2);
    paddle2.setPosition(displayProperties->topRightX - paddle2.getWidth() - space, (height - paddle2.getHeight()) / 2);
}