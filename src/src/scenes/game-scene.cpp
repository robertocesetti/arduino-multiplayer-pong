#include "game-scene.h"
#include <Arduino.h>

// https://xbm.jazzychad.net/

/* 1 x 64 */
static const unsigned char PROGMEM DOTTED_LINE[]  = {
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe,
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe,
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe};

GameScene::GameScene(GameEntity *ge) : gameEntities(ge)
{
    type = GAME;
}

GameScene::~GameScene()
{
}

void GameScene::tick()
{
    Ball *ball = gameEntities->getBall();
    Paddle *paddle1 = gameEntities->getPaddle1();
    Paddle *paddle2 = gameEntities->getPaddle2();

    ball->move();
    paddle1->move();
    paddle2->move();
    // moveUsingAI(paddle1, true);
    // moveUsingAI(paddle2, true);

    paddle1->collideWithBoard(displayProperties);
    paddle2->collideWithBoard(displayProperties);

    ball->collideWithBoard(displayProperties);
    ball->collideWithPaddle(paddle1);
    ball->collideWithPaddle(paddle2);
}

/*
void GameScene::moveUsingAI(Paddle *paddle, bool godMode)
{
    Ball* ball = gameEntities->getBall();

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
*/
void GameScene::render()
{
    drawBorder();

    display->drawBitmap(64, 0, DOTTED_LINE, 1, 64, SSD1306_WHITE);

    drawBall();
    drawPaddle(gameEntities->getPaddle1());
    drawPaddle(gameEntities->getPaddle2());
}

void GameScene::drawBorder()
{
    display->drawRect(displayProperties->topLeftX, displayProperties->topLeftY, displayProperties->bottomRightX, displayProperties->bottomRightY, WHITE);
}

void GameScene::drawBall()
{
    unsigned int ballX = gameEntities->getBall()->getPositionX();
    unsigned int ballY = gameEntities->getBall()->getPositionY();
    unsigned int ballR = gameEntities->getBall()->getRadius();
    display->fillCircle(ballX, ballY, ballR, WHITE);
}

void GameScene::drawPaddle(Paddle *paddle)
{
    int paddleX = paddle->getPositionX();
    int paddleY = paddle->getPositionY();
    int paddleWidth = paddle->getWidth();
    int paddleHeight = paddle->getHeight();
    display->fillRect(paddleX, paddleY, paddleWidth, paddleHeight, WHITE);
}