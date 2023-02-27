#include "paddle.h"
#include <Arduino.h>

Paddle::Paddle()
{
}

Paddle::~Paddle()
{
}

Collision Paddle::collideWithBoard(DisplayProperties *displayProperties)
{
    // Check for collisions with the top and bottom of the screen
    if ((positionY - 1) <= displayProperties->topLeftY)
    {
        positionY = displayProperties->topLeftY + 1;
        return BOARD;
    }

    if ((positionY + HEIGHT + 1) > displayProperties->bottomLeftY)
    {
        positionY = displayProperties->bottomLeftY - HEIGHT - 1;
        return BOARD;
    }

    return NONE;
}

