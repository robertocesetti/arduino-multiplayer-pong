#include "ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

bool Ball::collideWithBoard(DisplayProperties* displayProperties)
{
    bool collide = false;

    // Check for collisions with the top and bottom of the screen
    if ((positionY - RADIUS - 1) <= displayProperties->topLeftY || (positionY + RADIUS + 1) > displayProperties->bottomLeftY)
    {
        reverseVelocityY();
        collide = true;
    }
    
    // Check for collisions with the left and right of the screen
    if ((positionX - RADIUS - 1) <= displayProperties->topLeftX || (positionX + RADIUS + 1) > displayProperties->topRightX)
    {
        reverseVelocityX();
        collide = true;
    }

    return collide;
}