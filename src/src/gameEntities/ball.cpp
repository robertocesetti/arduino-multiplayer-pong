#include <Arduino.h>
#include "ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

Collision Ball::collideWithBoard(DisplayProperties *displayProperties)
{
    Collision collide = NONE;

    // Check for collisions with the top of the screen
    if ((positionY - RADIUS - 1) < displayProperties->topLeftY)
    {
        positionY = displayProperties->topLeftY + RADIUS + 1;
        reverseVelocityY();
        collide = BOARD;
    }

    // Check for collisions with the bottom of the screen
    if ((positionY + RADIUS + 1) > displayProperties->bottomLeftY)
    {
        positionY = displayProperties->bottomLeftY - RADIUS - 1;
        reverseVelocityY();
        collide = BOARD;
    }

    // Check for collisions with the left of the screen
    if ((positionX - RADIUS - 1) < displayProperties->topLeftX)
    {
        positionX = displayProperties->topLeftX + RADIUS + 1;
        reverseVelocityX();
        collide = LEFT;
    }

    // Check for collisions with the right of the screen
    if ((positionX + RADIUS + 1) > displayProperties->topRightX)
    {
        positionX = displayProperties->topRightX - RADIUS - 1;
        reverseVelocityX();
        collide = RIGTH;
    }

    return collide;
}

bool Ball::preparePositionMessage(PositionMessage *positionMessage)
{
    positionMessage->enityType = BALL;
    return Entity::preparePositionMessage(positionMessage);
}

void Ball::collideWithPaddle(Paddle *paddle)
{
    float paddleX = paddle->getPositionX();
    float paddleY = paddle->getPositionY();
    float paddleWidth = paddle->getWidth();
    float paddleHeight = paddle->getHeight();

    bool ballCollideOnLeftBorder = positionX + RADIUS > paddleX;
    bool ballCollideOnRightBorder = positionX - RADIUS < paddleX + paddleWidth;
    bool ballCollideOnTopBorder = positionY + RADIUS > paddleY;
    bool ballCollideOnBottomBorder = positionY - RADIUS < paddleY + paddleHeight;

    if (ballCollideOnLeftBorder && ballCollideOnRightBorder && ballCollideOnTopBorder && ballCollideOnBottomBorder)
    {
        // calculate angle between ball and paddle
        float angle = (positionY - (paddleY + paddleHeight / 2)) / (paddleHeight / 2);
        // add randomness based on angle and paddle velocity
        float randomness = -angle * paddle->getVelocityY();
        if (randomness <= 0.5f && randomness >= -0.5f)
            randomness = random(1, 7) / 10.0f;

        /*
        Serial.print("Angle: ");
        Serial.print(angle);
        Serial.print(", Randomness: ");
        Serial.println(randomness);

        Serial.println("Initial Velocity");
        Serial.print("VelocityX: ");
        Serial.print(velocityX);
        Serial.print(", VelocityY: ");
        Serial.println(velocityY);
        */

        if (positionY >= paddleY && positionY <= paddleY + paddleHeight) // Bal hit the paddle left/right side
        {
            float newX = positionX;

            if (ballCollideOnLeftBorder && velocityX > 0)
            {
                newX = paddleX - RADIUS;
            }
            else if (ballCollideOnRightBorder && velocityX < 0)
            {
                newX = paddleX + paddleWidth + RADIUS;
            }

            setPosition(newX, positionY);

            addRandomness(randomness / 5, randomness / 10);
            reverseVelocityX();
        }
        else if (positionX >= paddleX && positionX <= paddleX + paddleWidth) // Bal hit the paddle top/bottom side
        {
            float newY = positionY;

            if (ballCollideOnTopBorder && velocityY > 0)
            {
                newY = paddleY - RADIUS;
            }
            else if (ballCollideOnBottomBorder && velocityY < 0)
            {
                newY = paddleY + paddleHeight + RADIUS;
            }

            setPosition(positionX, newY);
            reverseVelocityY();
        }
        else // Ball hit the paddle corner
        {
            float newX = positionX;
            float newY = positionY;
            ballCollideOnTopBorder = positionY - RADIUS < paddleY && paddleY < positionY + RADIUS;
            ballCollideOnBottomBorder = positionY - RADIUS < paddleY + paddleHeight && paddleY + paddleHeight < positionY + RADIUS;

            if (ballCollideOnLeftBorder && velocityX > 0)
            {
                newX = paddleX - RADIUS;
            }
            else if (ballCollideOnRightBorder && velocityX < 0)
            {
                newX = paddleX + paddleWidth + RADIUS;
            }

            if (ballCollideOnTopBorder && velocityY > 0)
            {
                newY = paddleY - RADIUS;
            }
            else if (ballCollideOnBottomBorder && velocityY < 0)
            {
                newY = paddleY + paddleHeight + RADIUS;
            }

            setPosition(newX, newY);
            addRandomness(randomness / 10, randomness / 5);

            reverseVelocityX();
            reverseVelocityY();
        }

        /*
        Serial.println("Reversed Velocity");
        Serial.print("VelocityX: ");
        Serial.print(velocityX);
        Serial.print(", VelocityY: ");
        Serial.println(velocityY);
        */
    }
}

// Function that checks whether two boundaries intersect
bool Ball::intersect(const Boundary &r1, const Boundary &r2)
{
    return (r1.x < r2.x + r2.width && r1.x + r1.width > r2.x &&
            r1.y < r2.y + r2.height && r1.y + r1.height > r2.y);
}

// Set the randomness of the ball
void Ball::addRandomness(float randomX, float randomY)
{
    float vX = abs(velocityX) + randomX;
    float vY = abs(velocityY) + randomY;

    vX = constrain(vX, -MAX_VELOCITY_X, MAX_VELOCITY_X);
    vY = constrain(vY, -MAX_VELOCITY_Y, MAX_VELOCITY_Y);
    if (vX > 0 && vX <= MIN_VELOCITY_X)
        vX = MIN_VELOCITY_X;
    if (vX < 0 && vX >= -MIN_VELOCITY_X)
        vX = -MIN_VELOCITY_X;

    velocityX = velocityX < 0 ? -vX : vX;
    velocityY = velocityY < 0 ? -vY : vY;
}