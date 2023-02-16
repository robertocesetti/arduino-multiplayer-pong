#include "paddle.h"

void Paddle::setPosition(int pX, int pY)
{
    positionX = pX;
    positionY = pY;
}
int Paddle::getWidth()
{
    return WIDTH;
}

int Paddle::getHeight()
{
    return HEIGHT;
}