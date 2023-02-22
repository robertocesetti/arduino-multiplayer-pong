#include "pause-scene.h"

#include <Arduino.h>

PauseScene::PauseScene(/* args */)
{
    type = PAUSE;
}

PauseScene::~PauseScene()
{
}

void PauseScene::render()
{      
    //Serial.println("Rendering pause");
    // display->drawFrame(displayProperties->topLeftX, displayProperties->topLeftY, displayProperties->bottomRightX, displayProperties->bottomRightY);
    char strBuf[16]; // used for string formatting

    // Display the "You Lose" screen
    display->setFont(u8g_font_gdb20r); // switch to bigger font
    strcpy(strBuf, "PAUSE");
    display->drawStr((displayProperties->width - display->getStrPixelWidth(strBuf)) / 2, displayProperties->height  / 2, strBuf);
    display->setFont(u8g_font_gdb11r); // switch to bigger font
    strcpy(strBuf, "Press to restart");
    display->drawStr((displayProperties->width - display->getStrPixelWidth(strBuf)) / 2, displayProperties->height, strBuf);
    display->setFont(u8g_font_profont10r); // switch back to our normal font

}
