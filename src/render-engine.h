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
    void drawBall(Ball* ball);
    void drawPaddle(Paddle* paddle);
    void clearDisplay();
    void displayLose();

public:
    RenderEngine();
    ~RenderEngine();
    
    DisplayProperties* getDisplayProperties() { return displayProperties; }
    void render(GameEntity* gameEntities);
};
