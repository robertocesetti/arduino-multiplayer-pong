#include <Arduino_FreeRTOS.h>
#include <U8glib.h>
#include <Arduino.h>
#include "render-engine.h"
#include "gameEntities/game-entity.h"

RenderEngine::RenderEngine() : display(U8G_I2C_OPT_NONE | U8G_I2C_OPT_FAST)
{
    initDisplayProperties();
    clearDisplay();
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::initDisplayProperties()
{
    int w = display.getWidth();
    int h = display.getHeight();

    displayProperties = new DisplayProperties;
    displayProperties->width = w;
    displayProperties->height = h;

    displayProperties->topLeftX = 0;
    displayProperties->topLeftY = 0;

    displayProperties->topRightX = w - 1;
    displayProperties->topRightY = 0;

    displayProperties->bottomLeftX = 0;
    displayProperties->bottomLeftY = h - 1;

    displayProperties->bottomRightX = w - 1;
    displayProperties->bottomRightY = h - 1;
}

void RenderEngine::render(GameEntity *gameEntities)
{
    int fps = 0;
    unsigned long lastTime = millis();

    while (true)
    {
        fps++;
        if (millis() > lastTime + 1000)
        {
            Serial.print("FPS: ");
            Serial.println(fps);
            lastTime = millis();
            fps = 0;
        }

        display.firstPage();
        do
        {
            drawBorder();

            drawBall(gameEntities->getBall());
            drawPaddle(gameEntities->getPaddle1());
            drawPaddle(gameEntities->getPaddle2());
        } while (display.nextPage());
    }
}

void RenderEngine::drawBorder()
{
    // Draw the borders
    display.drawLine(displayProperties->topLeftX, displayProperties->topLeftY, displayProperties->topRightX, displayProperties->topRightY);             // top border
    display.drawLine(displayProperties->topLeftX, displayProperties->topLeftY, displayProperties->bottomLeftX, displayProperties->bottomLeftY);         // left border
    display.drawLine(displayProperties->bottomLeftX, displayProperties->bottomLeftY, displayProperties->bottomRightX, displayProperties->bottomRightY); // bottom border
    display.drawLine(displayProperties->topRightX, displayProperties->topRightY, displayProperties->bottomRightX, displayProperties->bottomRightY);     // right border
}

void RenderEngine::drawBall(Ball *ball)
{
    unsigned int ballX = ball->getPositionX();
    unsigned int ballY = ball->getPositionY();
    unsigned int ballR = ball->getRadius();
    display.drawDisc(ballX, ballY, ballR, U8G_DRAW_ALL);
}

void RenderEngine::drawPaddle(Paddle *paddle)
{
    int paddleX = paddle->getPositionX();
    int paddleY = paddle->getPositionY();
    int paddleWidth = paddle->getWidth();
    int paddleHeight = paddle->getHeight();
    display.drawBox(paddleX, paddleY, paddleWidth, paddleHeight);
}

void RenderEngine::displayLose()
{
    char strBuf[16]; // used for string formatting

    // Display the "You Lose" screen
    display.setFont(u8g_font_gdb20r); // switch to bigger font
    strcpy(strBuf, "TRY");
    display.drawStr((displayProperties->width - display.getStrPixelWidth(strBuf)) / 2, displayProperties->height / 2, strBuf);
    strcpy(strBuf, "AGAIN!");
    display.drawStr((displayProperties->width - display.getStrPixelWidth(strBuf)) / 2, displayProperties->height, strBuf);
    display.setFont(u8g_font_profont10r); // switch back to our normal font
}

void RenderEngine::clearDisplay()
{
    // Clear the screen
    display.firstPage();
    do
    {
    } while (display.nextPage());
}