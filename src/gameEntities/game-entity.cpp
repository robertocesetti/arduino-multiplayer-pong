#include "game-entity.h"

GameEntity::GameEntity()
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::initialize(int width, int height)
{
    ball.setPosition((width - ball.getRadius()) / 2, (height - ball.getRadius()) / 2);
    paddle1.setPosition(paddle1.getWidth(), (height - paddle1.getHeight()) / 2);
    paddle2.setPosition(width - paddle2.getWidth(), (height - paddle2.getHeight()) / 2);
}