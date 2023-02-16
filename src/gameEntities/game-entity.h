#include "ball.h"
#include "paddle.h"

class GameEntity
{
private:
    Ball ball {};
    Paddle paddle1 {};
    Paddle paddle2 {};
    
public:
    GameEntity();
    ~GameEntity();

    void initialize(int width, int heigth);
    Ball getBall();
    Paddle getPaddle1();
    Paddle getPaddle2();
};
