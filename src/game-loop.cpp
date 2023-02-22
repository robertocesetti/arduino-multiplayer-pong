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
    ball->updateVelocity(1, 1);
    paddle1->updateVelocity(0, 2);
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
    moveUsingAI(paddle1, ball, true);
    //moveUsingAI(paddle2, ball, true);
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

    // paddle2->collideWithBoard(displayProperties);
    if (paddle2->collideWithBoard(displayProperties))
        paddle2->reverseVelocityY();

    ball->collideWithBoard(displayProperties);
    ball->collideWithPaddle(paddle1);
    ball->collideWithPaddle(paddle2);
}

void GameLoop::moveUsingAI(Paddle *paddle, Ball *ball, bool godMode = false)
{
    if (godMode)
    {
        paddle->setVelocityY(ball->getVelocityY());
    }
    else
    {
        if (ball->getVelocityX() < 0 && (ball->getPositionX() - paddle->getPositionX()) < 70)
        {
            if (paddle->getVelocityY() == 0.0f)
                paddle->setVelocityY(0.5f);

            if (ball->getVelocityY() > 0 && paddle->getVelocityY() < 0 || ball->getVelocityY() < 0 && paddle->getVelocityY() > 0)
            {
                paddle->setVelocityY(paddle->getVelocityY() * -1);
            }
        }
        else
        {
            paddle->setVelocityY(0.0f);
        }
    }

    paddle->move();
}
