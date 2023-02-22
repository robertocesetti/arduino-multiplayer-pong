#pragma once

#include <U8glib.h>
#include "../display-properties.h"

enum SceneType {
    GAME
};

class Scene
{
protected:
    SceneType type;
    U8GLIB_SSD1306_128X64 *display;
    DisplayProperties *displayProperties;

public:
    Scene();
    ~Scene();

    void initialize(U8GLIB_SSD1306_128X64 *display, DisplayProperties *displayProperties);
    virtual void render();

    SceneType getSceneType() {return type;}
};
