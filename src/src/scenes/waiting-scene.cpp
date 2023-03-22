#include "waiting-scene.h"

WaitingScene::WaitingScene(){
    type = WAITING;
}

WaitingScene::~WaitingScene()
{
}

void WaitingScene::render()
{
  display->setFont();
  display->setTextSize(2); // Draw 2X-scale text
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(38, 12);
  display->println(F("READY"));

  display->setTextSize(1);
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(20, 56);
  display->println(F("Waiting the other"));

  Scene::render();
}
