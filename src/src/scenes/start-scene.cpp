#include "start-scene.h"
#include <Arduino.h>

StartScene::StartScene(/* args */)
{
    type = START;
}
StartScene::~StartScene()
{
}

char strBuf[17]; // used for string formatting

void StartScene::render()
{
    display->setFont(u8g2_font_t0_14b_me); // switch to bigger font
    strcpy(strBuf, "START");
    display->drawStr((displayProperties->width - display->getStrWidth(strBuf)) / 2, displayProperties->height / 2, strBuf);
    //display->setFont(u8g_font_gdb11r); // switch to bigger font
    strcpy(strBuf, "Press the button");
    display->drawStr((displayProperties->width - display->getStrWidth(strBuf)) / 2, displayProperties->height, strBuf);
    display->setFont(u8g2_font_t0_14b_me); // switch back to our normal font
}