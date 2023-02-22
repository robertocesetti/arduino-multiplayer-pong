#include "final-score-scene.h"
#include <U8glib.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

FinalScoreScene::FinalScoreScene(/* args */)
{
    type = SCORE;
}

FinalScoreScene::~FinalScoreScene()
{
}

void FinalScoreScene::render()
{  
    char strBuf[16]; // used for string formatting

    // Display the "You Lose" screen
    display->setFont(u8g_font_gdb20r); // switch to bigger font
    strcpy(strBuf, "TRY");
    display->drawStr((displayProperties->width - display->getStrPixelWidth(strBuf)) / 2, displayProperties->height / 2, strBuf);
    strcpy(strBuf, "AGAIN!");
    display->drawStr((displayProperties->width - display->getStrPixelWidth(strBuf)) / 2, displayProperties->height, strBuf);
    display->setFont(u8g_font_profont10r); // switch back to our normal fon->
}