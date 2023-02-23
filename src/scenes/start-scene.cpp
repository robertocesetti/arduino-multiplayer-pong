#include "start-scene.h"
#include <U8glib.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

StartScene::StartScene(/* args */)
{
    type = START;
}
StartScene::~StartScene()
{
}

char strBuf[16]; // used for string formatting

void StartScene::render()
{
    display->setFont(u8g_font_gdb20r); // switch to bigger font
    strcpy(strBuf, "START");
    display->drawStr((displayProperties->width - display->getStrPixelWidth(strBuf)) / 2, displayProperties->height / 2, strBuf);
    display->setFont(u8g_font_gdb11r); // switch to bigger font
    strcpy(strBuf, "Press the button");
    display->drawStr((displayProperties->width - display->getStrPixelWidth(strBuf)) / 2, displayProperties->height, strBuf);
    display->setFont(u8g_font_profont10r); // switch back to our normal font
}