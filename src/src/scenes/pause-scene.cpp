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
    char strBuf[18]; // used for string formatting

    // Display the "You Lose" screen
    display->setFont(u8g2_font_unifont_t_symbols); // switch to bigger font
    strcpy(strBuf, "PAUSE");
    display->drawStr((displayProperties->width - display->getStrWidth(strBuf)) / 2, displayProperties->height  / 2, strBuf);
    display->setFont(u8g2_font_unifont_t_symbols); // switch to bigger font
    strcpy(strBuf, "Press to restart");
    display->drawStr((displayProperties->width - display->getStrWidth(strBuf)) / 2, displayProperties->height, strBuf);
    display->setFont(u8g2_font_unifont_t_symbols); // switch back to our normal font

}
