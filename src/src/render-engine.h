#pragma once

#include <U8g2lib.h>
#include "display-properties.h"
#include "scenes/scene.h"

class RenderEngine
{
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;
    DisplayProperties* displayProperties;
    Scene* currentScene;
    
    void initDisplayProperties();
    void clearDisplay();
    void displayLose();

public:
    RenderEngine();
    ~RenderEngine();
    
    DisplayProperties* getDisplayProperties() { return displayProperties; }
    void changeScene(Scene* scene);
    Scene* getCurrentScene(){ return currentScene;}
    void render();
};