#pragma once

#include "ball.h"
#include "paddle.h"
#include "../display-properties.h"

class GameEntity
{
private:
    Ball ball;
    Paddle paddle1;
    Paddle paddle2;
    
public:
    GameEntity();
    ~GameEntity();

    void initialize(DisplayProperties *displayProperties);
    Ball* getBall(){return &ball;};
    Paddle* getPaddle1(){return &paddle1;};
    Paddle* getPaddle2(){return &paddle2;};
};
