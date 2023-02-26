#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../display-properties.h"

enum SceneType
{
    GAME,
    SCORE,
    START,
    PAUSE
};

class Scene
{
protected:
    SceneType type;
    Adafruit_SSD1306 *display;
    DisplayProperties *displayProperties;
    bool rendered;

public:
    Scene();
    virtual ~Scene();

    void initialize(Adafruit_SSD1306 *display, DisplayProperties *displayProperties);
    virtual void render() = 0;
    virtual void tick(){};
    virtual bool useTick() { return false; }
    virtual bool renderOnce() { return rendered; }

    SceneType getSceneType() { return type; }
};
