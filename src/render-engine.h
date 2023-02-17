#pragma once

#include <U8glib.h>
#include "gameEntities/game-entity.h"
#include "display-properties.h"

class RenderEngine
{
private:
    U8GLIB_SSD1306_128X64 display;
    DisplayProperties* displayProperties;
    
    void initDisplayProperties();
    void drawBorder();
    void clearDisplay();
    void displayLose();

public:
    RenderEngine();
    ~RenderEngine();
    
    DisplayProperties* getDisplayProperties() { return displayProperties; }
    void render(GameEntity* gameEntities);
};
