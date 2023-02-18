#include "ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

bool Ball::collideWithBoard(DisplayProperties *displayProperties)
{
    bool collide = false;

    // Check for collisions with the top of the screen
    if ((positionY - RADIUS - 1) < displayProperties->topLeftY)
    {
        positionY = displayProperties->topLeftY + RADIUS + 1;
        reverseVelocityY();
        collide = true;
    }

    // Check for collisions with the bottom of the screen
    if ((positionY + RADIUS + 1) > displayProperties->bottomLeftY)
    {
        positionY = displayProperties->bottomLeftY - RADIUS - 1;
        reverseVelocityY();
        collide = true;
    }

    // Check for collisions with the left of the screen
    if ((positionX - RADIUS - 1) < displayProperties->topLeftX)
    {
        positionX = displayProperties->topLeftX + RADIUS + 1;
        reverseVelocityX();
        collide = true;
    }

        // Check for collisions with the right of the screen
    if ((positionX + RADIUS + 1) > displayProperties->topRightX)
    {
        positionX = displayProperties->topRightX - RADIUS - 1;
        reverseVelocityX();
        collide = true;
    }

    /*

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
    */

    return collide;
}