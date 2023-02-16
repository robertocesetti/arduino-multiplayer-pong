#include "game-engine.h"

void start(GameEngineStat *gameEngine) {
    if(gameEngine->running) return;

    gameEngine->running = 1;
    // network.init()
    // render.changeScene(START);
    
    initializeRender(gameEngine->renderEngine);
}

static void _gameLoop(){

}

void end() {

}