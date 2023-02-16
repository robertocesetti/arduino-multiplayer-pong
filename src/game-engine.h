#include "render-engine.h"

typedef enum SceneType { START, GAME, END } SceneType;

typedef struct GameEngineStat {
    unsigned short running;
    RenderEngine* renderEngine;
    SceneType scene;
} GameEngineStat;

GameEngineStat* create();

void start();

void end();