#pragma once

#include <U8glib.h>
#include "display-properties.h"
#include "scenes/scene.h"

class RenderEngine
{
private:
    U8GLIB_SSD1306_128X64 display;
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