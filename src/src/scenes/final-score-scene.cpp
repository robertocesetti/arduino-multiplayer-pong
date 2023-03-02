#include "final-score-scene.h"
#include <Arduino.h>
#include "../network-manager.h"
// #include <Arduino_FreeRTOS.h>

FinalScoreScene::FinalScoreScene(/* args */)
{
    type = SCORE;
}

FinalScoreScene::~FinalScoreScene()
{
}

void FinalScoreScene::render()
{
    display->setTextSize(2); // Draw 2X-scale text
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(10, 20);

    if (NetworkManager::getInstance()->getMyPaddle()->won())
        display->println(F("YOU WIN!"));
    else
        display->println(F("YOU LOSE!"));

    Scene::render();
}