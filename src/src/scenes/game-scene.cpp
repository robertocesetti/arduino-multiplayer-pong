#include "game-scene.h"
#include <Arduino.h>
#include <Fonts/Org_01.h>
#include "../gameEntities/collision.h"
#include "../network-manager.h"

// https://xbm.jazzychad.net/

/* 1 x 64 */
static const unsigned char PROGMEM DOTTED_LINE[] = {
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe,
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe,
    0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfe};

const int SPACE = 15;

GameScene::GameScene(SceneManager *sm, GameEntity *ge) : sceneManager(sm), gameEntities(ge)
{
    type = GAME;
}

GameScene::~GameScene()
{
}

void GameScene::tick()
{
    Paddle *paddle1 = gameEntities->getPaddle1();
    if (NetworkManager::getInstance()->isSlave())
    {
        paddle1->move();
        paddle1->collideWithBoard(displayProperties);

        return;
    }

    // Serial.println("<--GameTick-->");
    Ball *ball = gameEntities->getBall();
    Paddle *paddle2 = gameEntities->getPaddle2();

    ball->move();
    paddle2->move();
    // moveUsingAI(paddle1, true);
    // moveUsingAI(paddle2, true);

    paddle2->collideWithBoard(displayProperties);

    ball->collideWithPaddle(paddle1);
    ball->collideWithPaddle(paddle2);

    Collision collision = ball->collideWithBoard(displayProperties);
    switch (collision)
    {
    case LEFT:
        addPoint(paddle2);
        break;
    case RIGTH:
        addPoint(paddle1);
        break;
    default:
        break;
    }
}

void GameScene::addPoint(Paddle *paddle)
{
    paddle->addPoint();
    gameEntities->resetBall();
    if (paddle->getScore() >= MAX_SCORE)
    {
        sceneManager->changeScene(SCORE);
    }
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
    // Serial.println("GameRender");
    drawBorder();
    drawScore();

    display->drawXBitmap(64, 0, DOTTED_LINE, 1, 64, SSD1306_WHITE);

    drawBall();
    drawPaddle(gameEntities->getPaddle1());
    drawPaddle(gameEntities->getPaddle2());

    Scene::render();
}

void GameScene::drawBorder()
{
    // top line
    display->drawFastHLine(displayProperties->topLeftX, displayProperties->topLeftY, displayProperties->width, SSD1306_WHITE);
    // bottom line
    display->drawFastHLine(displayProperties->bottomLeftX, displayProperties->bottomLeftY, displayProperties->width, SSD1306_WHITE);
}

void GameScene::drawScore()
{
    display->setTextSize(1);
    display->setFont(&Org_01);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(displayProperties->topLeftX + 2, 6);
    display->print(gameEntities->getPaddle1()->getScore());

    display->setFont(&Org_01);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(displayProperties->topRightX - 6, 6);
    display->print(gameEntities->getPaddle2()->getScore());
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