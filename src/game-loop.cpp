#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "game-loop.h"

static const int SKEW = 3;
static const int UPS_SET = 30;
static const int MAXBOUNCEANGLE = 75;
static const int BALL_SPEED = 1;

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::update(GameEntity *gameEntities)
{
    Ball *ball = gameEntities->getBall();
    Paddle *paddle1 = gameEntities->getPaddle1();
    Paddle *paddle2 = gameEntities->getPaddle2();
    ball->updateVelocity(1, 5);
    paddle1->updateVelocity(0, 0.5f);
    // paddle2->updateVelocity(0, -0.2f);

    double MS_PER_UPDATE = 1000.0 / UPS_SET;
    unsigned long current = millis();
    unsigned long previous = current;
    unsigned long lastCheck = current;
    unsigned long elapsed = 0L;
    double lag = 0.0;
    int ups = 0;

    while (true)
    {
        current = millis();
        elapsed = current - previous;
        previous = current;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            ups++;
            tick(ball, paddle1, paddle2);
            lag -= MS_PER_UPDATE;
        }

        if (current - lastCheck >= 1000)
        {
            lastCheck = current;
            Serial.print(F("UPS: "));
            Serial.println(ups);
            ups = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void GameLoop::tick(Ball *ball, Paddle *paddle1, Paddle *paddle2)
{

    ball->move();
    paddle1->moveUsingAI(ball);
    paddle2->moveUsingAI(ball, true);

    if (paddle1->collideWithBoard(displayProperties))
    {
        paddle1->reverseVelocityY();

        /*
        float velocity = random(1, 10) / 10.0f;
        if(paddle1->getVelocityY() < 0){
            velocity*=-1;
        }
        paddle1->updateVelocity(0, velocity);
        */
    }

    // paddle2->collideWithBoard(displayProperties);
    if (paddle2->collideWithBoard(displayProperties))
        paddle2->reverseVelocityY();

    ball->collideWithBoard(displayProperties);

    checkCollisionWithPaddle(ball, paddle1);
    checkCollisionWithPaddle(ball, paddle2);
}

void GameLoop::checkCollisionWithPaddle(Ball *ball, Paddle *paddle)
{
    bool ballIsOnLeft = ball->getPositionX() + ball->getRadius() > paddle->getPositionX();
    bool ballIsOnRight = ball->getPositionX() - ball->getRadius() < paddle->getPositionX() + paddle->getWidth();
    bool ballIsOnTop = ball->getPositionY() + ball->getRadius() > paddle->getPositionY();
    bool ballIsOnBottom = ball->getPositionY() - ball->getRadius() < paddle->getPositionY() + paddle->getHeight();

    // Checks for the collisions with the paddle
    if (ballIsOnLeft && ballIsOnRight && ballIsOnTop && ballIsOnBottom)
    {
        float newX = ball->getPositionX();
        float newY = ball->getPositionY();

        if (ball->getPositionY() >= paddle->getPositionY() && ball->getPositionY() <= paddle->getPositionY() + paddle->getHeight())
        {
            if (ballIsOnLeft && ball->getVelocityX() > 0)
            {
                newX = paddle->getPositionX() - ball->getRadius();
            }
            if (ballIsOnRight && ball->getVelocityX() < 0)
            {
                newX = paddle->getPositionX() + paddle->getWidth() + ball->getRadius();
            }
            ball->reverseVelocityX();
        }
        else if (ball->getPositionX() >= paddle->getPositionX() && ball->getPositionX() <= paddle->getPositionX() + paddle->getWidth())
        {
            if (ballIsOnTop && ball->getVelocityY() > 0)
            {
                newY = paddle->getPositionY() - ball->getRadius();
            }
            if (ballIsOnBottom && ball->getVelocityY() < 0)
            {
                newY = paddle->getPositionY() + paddle->getHeight() + ball->getRadius();
            }
            ball->reverseVelocityY();
        }
        else
        {
            if (ballIsOnLeft && ball->getVelocityX() > 0)
            {
                newX = paddle->getPositionX() - ball->getRadius();
            }
            if (ballIsOnRight && ball->getVelocityX() < 0)
            {
                newX = paddle->getPositionX() + paddle->getWidth() + ball->getRadius();
            }
            ball->reverseVelocityX();
            
            if (ballIsOnTop && ball->getVelocityY() > 0)
            {
                newY = paddle->getPositionY() - ball->getRadius();
            }
            if (ballIsOnBottom && ball->getVelocityY() < 0)
            {
                newY = paddle->getPositionY() + paddle->getHeight() + ball->getRadius();
            }
            ball->reverseVelocityY();
        }

        ball->setPosition(newX, newY);

        /*
        // -6 a +6 h=12
        float relativeIntersectY = (paddle->getPositionY()+(paddle->getHeight()/2.0f)) - ball->getPositionY();
        // -1 a +1
        float normalizedRelativeIntersectionY = (relativeIntersectY/(paddle->getHeight()/2.0f));

        float bounceAngle = normalizedRelativeIntersectionY * MAXBOUNCEANGLE;

        float ballVx = ball->getVelocityX()*-1;
        float ballVy = 2 * -sin(bounceAngle);

        ball->updateVelocity(ballVx, ballVy);
        */

        /*
        ball->reverseVelocityX();
        // Add some randomness to the ball motion, based on the current skew setting
        int randomVelocity = random(1, SKEW + 1);
        ball->setVelocityY(randomVelocity);
        if (ball->getPositionY() <= paddle->getPositionY() + (3 * paddle->getHeight()) / 7)
            ball->reverseVelocityY();
*/
    }
}

/*

   |
 o |
   |
  o|


*/