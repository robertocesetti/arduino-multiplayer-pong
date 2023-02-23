#include "scene.h"
#include <Arduino.h>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::initialize(U8G2_SSD1306_128X64_NONAME_F_HW_I2C *display, DisplayProperties *displayProperties)
{
    this->display = display;
    this->displayProperties = displayProperties;
}