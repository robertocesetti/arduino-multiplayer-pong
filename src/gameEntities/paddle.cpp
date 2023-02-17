#include "paddle.h"
#include <Arduino.h>

Paddle::Paddle()
{
}

Paddle::~Paddle()
{
}

bool Paddle::collideWithBoard(DisplayProperties *displayProperties)
{
    // Check for collisions with the top and bottom of the screen
    if ((positionY - 1) <= displayProperties->topLeftY)
    {
        positionY = displayProperties->topLeftY + 1;
        return true;
    }

    if ((positionY + HEIGHT + 1) > displayProperties->bottomLeftY)
    {
        positionY = displayProperties->bottomLeftY - HEIGHT - 1;
        return true;
    }

    return false;
}

void Paddle::moveUsingAI(Ball *ball, bool godMode = false)
{
    if (godMode)
    {
        velocityY = ball->getVelocityY();
    }
    else
    {
        if (ball->getVelocityX() < 0 && (ball->getPositionX() - positionX) < 70)
        {
            if (velocityY == 0.0f)
                velocityY = 0.5f;

            if (ball->getVelocityY() > 0 && velocityY < 0 || ball->getVelocityY() < 0 && velocityY > 0)
            {
                velocityY *= -1;
            }
        }
        else
        {
            setVelocityY(0.0f);
        }
    }

    move();
}