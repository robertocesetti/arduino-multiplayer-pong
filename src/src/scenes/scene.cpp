#include "scene.h"
#include <Arduino.h>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::initialize(Adafruit_SSD1306 *display, DisplayProperties *displayProperties)
{
    this->display = display;
    this->displayProperties = displayProperties;
}