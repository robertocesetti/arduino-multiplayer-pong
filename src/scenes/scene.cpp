#include "scene.h"
#include <Arduino.h>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::initialize(U8GLIB_SSD1306_128X64 *display, DisplayProperties *displayProperties)
{
    this->display = display;
    this->displayProperties = displayProperties;
}