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
    while (true)
    {
        display.firstPage();
        do
        {
            drawBorder();

            int ballX = gameEntities->getBall()->getPositionX();
            int ballY = gameEntities->getBall()->getPositionY();
            int ballR = gameEntities->getBall()->getRadius();

            display.drawDisc(ballX, ballY, ballR, U8G_DRAW_ALL);
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

void RenderEngine::displayLose()
{
    char strBuf[16]; // used for string formatting

    // Display the "You Lose" screen
    display.setFont(u8g_font_gdb20r); // switch to bigger font
    strcpy(strBuf, "TRY");
    display.drawStr((displayProperties -> width - display.getStrPixelWidth(strBuf)) / 2, displayProperties -> height / 2, strBuf);
    strcpy(strBuf, "AGAIN!");
    display.drawStr((displayProperties -> width - display.getStrPixelWidth(strBuf)) / 2, displayProperties -> height, strBuf);
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