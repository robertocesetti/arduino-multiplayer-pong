#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display-properties.h"
#include "scenes/scene.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET -1 // Reset pin
#define SCREEN_ADDRESS 0x3C

class RenderEngine
{
private:
    Adafruit_SSD1306 display;
    DisplayProperties* displayProperties;
    Scene* currentScene;
    
    void initDisplayProperties();

public:
    RenderEngine();
    ~RenderEngine();
    
    DisplayProperties* getDisplayProperties() { return displayProperties; }
    void changeScene(Scene* scene);
    Scene* getCurrentScene(){ return currentScene;}
    void render();
};