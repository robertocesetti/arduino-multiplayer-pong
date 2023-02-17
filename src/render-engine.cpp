#include <Arduino_FreeRTOS.h>
#include <U8glib.h>
#include <Arduino.h>
#include "render-engine.h"
#include "gameEntities/game-entity.h"

RenderEngine::RenderEngine() : display(U8G_I2C_OPT_NONE | U8G_I2C_OPT_FAST)
                               , width(display.getWidth())
                               , height(display.getHeight())
{
    this->clearDisplay();
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::render2()
{
    Serial.println("render2");
    //while(true){
        display.firstPage();
        do
        {
            int ballX = 10;
            int ballY = 20;
            int ballR = 2;
            
            display.drawDisc(ballX, ballY, ballR, U8G_DRAW_ALL);
        } while (display.nextPage());
    //}
}

void RenderEngine::render(GameEntity* gameEntities)
{

    while(true){
        display.firstPage();
        do
        {
            int ballX = gameEntities->getBall().getPositionX();
            int ballY = gameEntities->getBall().getPositionY();
            int ballR = gameEntities->getBall().getRadius();
            
            display.drawDisc(ballX, ballY, ballR, U8G_DRAW_ALL);
        } while (display.nextPage());
    }
}

void RenderEngine::displayLose()
{
    char strBuf[16]; // used for string formatting

    // Display the "You Lose" screen
    display.setFont(u8g_font_gdb20r); // switch to bigger font
    strcpy(strBuf, "TRY");
    display.drawStr((width - display.getStrPixelWidth(strBuf)) / 2, height / 2, strBuf);
    strcpy(strBuf, "AGAIN!");
    display.drawStr((width - display.getStrPixelWidth(strBuf)) / 2, height, strBuf);
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