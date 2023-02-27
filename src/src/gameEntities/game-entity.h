#pragma once

#include "ball.h"
#include "paddle.h"
#include "../display-properties.h"

class GameEntity
{
private:
    DisplayProperties *displayProperties;
    Ball ball;
    Paddle paddle1;
    Paddle paddle2;

public:
    GameEntity();
    ~GameEntity();

    void initialize(DisplayProperties *displayProperties);
    void resetBall();
    void resetGame();
    Ball *getBall() { return &ball; };
    Paddle *getPaddle1() { return &paddle1; };
    Paddle *getPaddle2() { return &paddle2; };
};
