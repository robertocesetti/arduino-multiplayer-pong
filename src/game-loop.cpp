#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "game-loop.h"

static const int SKEW = 3;

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
    ball->updateVelocity(0.5f, 1);

    paddle1->updateVelocity(0, 0.5f);
    //paddle2->updateVelocity(0, -0.2f);

    int ups = 0;
    unsigned long lastTime = millis();

    // TODO Fix UPS

    while (true)
    {
        ups++;
        if (millis() > lastTime + 1000)
        {
            Serial.print("UPS: ");
            Serial.println(ups);
            lastTime = millis();
            ups = 0;
        }

        ball->move();
        paddle1->moveUsingAI(ball, true);
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

        //paddle2->collideWithBoard(displayProperties);
        if (paddle2->collideWithBoard(displayProperties))
            paddle2->reverseVelocityY();

        ball->collideWithBoard(displayProperties);

        checkCollisionWithPaddle(ball, paddle1);
        checkCollisionWithPaddle(ball, paddle2);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
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
        if (ballIsOnLeft && ball->getVelocityX() > 0)
        {
            newX = paddle->getPositionX() - ball->getRadius();
        }
        if (ballIsOnRight && ball->getVelocityX() < 0)
        {
            newX = paddle->getPositionX() + paddle->getWidth() + ball->getRadius();
        }
        if (ballIsOnTop)
        {
            newY = paddle->getPositionY() + ball->getRadius();
        }
        if (ballIsOnBottom)
        {
            newY = paddle->getPositionY() + paddle->getHeight() - ball->getRadius();
        }
        ball->setPosition(newX, newY);

        ball->reverseVelocityX();

        // Add some randomness to the ball motion, based on the current skew setting
        int randomVelocity = random(1, SKEW + 1);
        ball->setVelocityY(randomVelocity);
        if (ball->getPositionY() <= paddle->getPositionY() + (3 * paddle->getHeight()) / 7)
            ball->reverseVelocityY();
    }
}

/* FIX UPS

    https://stackoverflow.com/questions/5405034/attempting-to-create-a-stable-game-engine-loop

    long maxWorkingTimePerFrame = 1000 / 20;  //this is optional
    unsigned long lastStartTime = millis();
    while(true)
    {
        long elapsedTime = millis() - lastStartTime;
        lastStartTime = millis();

        // update objects elapsedTime = deltaTime;
        Serial.println(elapsedTime);
        ups++;
        if (lastStartTime > lastTime + 1000)
        {
            Serial.print("UPS: ");
            Serial.println(ups);
            lastTime = lastStartTime;
            ups = 0;
        }
        ball->move();
        checkCollisionWithBoard(ball);
        checkCollisionWithPaddle(ball, paddle1);
        checkCollisionWithPaddle(ball, paddle2);


        //enforcing a maximum framerate here is optional...you don't need to sleep the thread
        long processingTimeForCurrentFrame = millis() - lastStartTime;
        if(processingTimeForCurrentFrame < maxWorkingTimePerFrame)
        {
            vTaskDelay(pdMS_TO_TICKS(maxWorkingTimePerFrame - processingTimeForCurrentFrame));
        }
    }*/
