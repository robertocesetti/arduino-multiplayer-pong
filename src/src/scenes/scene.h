#pragma once

#include <U8g2lib.h>
#include "../display-properties.h"

enum SceneType
{
    GAME = 0,
    SCORE,
    START,
    PAUSE
};

class Scene
{
protected:
    SceneType type;
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C *display;
    DisplayProperties *displayProperties;

public:
    Scene();
    virtual ~Scene();

    void initialize(U8G2_SSD1306_128X64_NONAME_F_HW_I2C *display, DisplayProperties *displayProperties);
    virtual void render() = 0;

    SceneType getSceneType() { return type; }
};
