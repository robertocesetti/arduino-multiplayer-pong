#include "connection-scene.h"
#include "../network-manager.h"

ConnectionScene::ConnectionScene(){
    type = CONNECTION;
}

ConnectionScene::~ConnectionScene()
{
}

void ConnectionScene::render()
{
  display->setTextSize(1); // Draw 2X-scale text
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(0, 5);
  display->println(F("Connection..."));

  display->setCursor(0, 20);
  String log = NetworkManager::getInstance()->getLog();
  if(log != nullptr) display->println(log);

  Scene::render();
}
