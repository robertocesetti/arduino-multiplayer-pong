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
    paddle2->updateVelocity(0, -0.2f);

    int ups = 0;
    unsigned long lastTime = millis();

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
        paddle2->move();


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
    // Checks for the collisions with the paddle
    if ((ball->getPositionX() + ball->getRadius() > paddle->getPositionX() && ball->getPositionX() - ball->getRadius() < paddle->getPositionX() + paddle->getWidth()) && ball->getPositionY() > paddle->getPositionY() && ball->getPositionY() < (paddle->getPositionY() + paddle->getHeight()))
    {
        ball->reverseVelocityX();

        // Add some randomness to the ball motion, based on the current skew setting
        int randomVelocity = random(1, SKEW + 1);
        ball->setVelocityY(randomVelocity);
        if (ball->getPositionY() <= paddle->getPositionY() + (3 * paddle->getHeight()) / 7)
            ball->reverseVelocityY();
    }
}
