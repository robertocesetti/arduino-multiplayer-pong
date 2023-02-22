#include "game-scene.h"
#include <Arduino.h>

// https://xbm.jazzychad.net/

/* 1 x 64 */
static const unsigned char DOTTED_LINE[] PROGMEM = {
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe,
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe,
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe};

GameScene::GameScene(GameEntity* ge) :gameEntities(ge)
{
    type = GAME;
}

GameScene::~GameScene()
{
}

void GameScene::render()
{
    drawBorder();

    display->drawXBMP(64, 0, 1, 64, DOTTED_LINE);

    drawBall();
    drawPaddle(gameEntities->getPaddle1());
    drawPaddle(gameEntities->getPaddle2());
}

void GameScene::drawBorder()
{
    display->drawFrame(displayProperties->topLeftX, displayProperties->topLeftY, displayProperties->bottomRightX, displayProperties->bottomRightY);
}

void GameScene::drawBall()
{
    unsigned int ballX = gameEntities->getBall()->getPositionX();
    unsigned int ballY = gameEntities->getBall()->getPositionY();
    unsigned int ballR = gameEntities->getBall()->getRadius();
    display->drawDisc(ballX, ballY, ballR, U8G_DRAW_ALL);
}

void GameScene::drawPaddle(Paddle* paddle)
{
    int paddleX = paddle->getPositionX();
    int paddleY = paddle->getPositionY();
    int paddleWidth = paddle->getWidth();
    int paddleHeight = paddle->getHeight();
    display->drawBox(paddleX, paddleY, paddleWidth, paddleHeight);
}