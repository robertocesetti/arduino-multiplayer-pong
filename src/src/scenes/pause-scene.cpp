#include "pause-scene.h"

#include <Arduino.h>

PauseScene::PauseScene(GameEntity *ge) : gameEntities(ge)
{
    type = PAUSE;
}

PauseScene::~PauseScene()
{
}

void PauseScene::render()
{
    display->setTextSize(2); // Draw 2X-scale text
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(10, 0);
    display->println(F("PAUSE"));

    unsigned int ballX = gameEntities->getBall()->getPositionX();
    unsigned int ballY = gameEntities->getBall()->getPositionY();
    unsigned int ballR = gameEntities->getBall()->getRadius();
    display->fillCircle(ballX, ballY, ballR, WHITE);

    Scene::render();
    /*
        char strBuf[20]; // used for string formatting

        // Display the "You Lose" screen
        display->setFont(u8g_font_gdb20r); // switch to bigger font
        strcpy(strBuf, "PAUSE");
        display->drawStr((displayProperties->width - display->getStrWidth(strBuf)) / 2, displayProperties->height  / 2, strBuf);
        display->setFont(u8g_font_gdb11r); // switch to bigger font
        strcpy(strBuf, "Press to restart");
        display->drawStr((displayProperties->width - display->getStrWidth(strBuf)) / 2, displayProperties->height, strBuf);
        display->setFont(u8g_font_profont10r); // switch back to our normal font
        */
}
