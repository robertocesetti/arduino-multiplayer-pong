#include <Arduino.h>
#include "scene-manager.h"
#include "start-scene.h"
#include "game-scene.h"
#include "final-score-scene.h"
#include "pause-scene.h"
#include "../game-task-manager.h"

SceneManager::SceneManager(GameEntity *ge, RenderEngine *re, GameLoop *gl) : gameEntities(ge), renderEngine(re), gameLoop(gl)
{
    createScenes();
}

SceneManager::~SceneManager()
{
}

void SceneManager::createScenes()
{
    auto gs = new GameScene(this, gameEntities);
    auto fs = new FinalScoreScene();
    auto ss = new StartScene();
    auto ps = new PauseScene();

    scenes[0] = gs;
    scenes[1] = fs;
    scenes[2] = ss;
    scenes[3] = ps;

    Serial.println("Scene loaded:");
    for (Scene *scene : scenes)
    {
        Serial.printf("%i -- %p\n", scene->getSceneType(), scene);
    }
}

void SceneManager::changeScene(SceneType sceneType)
{
    for (Scene *scene : scenes)
    {
        if (scene->getSceneType() == sceneType)
        {
            Serial.printf("Change scene: %i -- %p\n", scene->getSceneType(), scene);
            renderEngine->changeScene(scene);
            gameLoop->changeScene(scene);

            // Serial.printf("Try to suspend %s, from status %i\n", pcTaskGetName(GameTaskManager::getInstance()->tasks.inputTaskHandler), eTaskGetState(GameTaskManager::getInstance()->tasks.inputTaskHandler));

            return;
        }
    }
}

void SceneManager::changeScene()
{
    switch (getCurrentScene())
    {
    case START:
    case PAUSE:
        changeScene(GAME);
        break;
    case GAME:
        changeScene(PAUSE);
        break;
    case SCORE:
        gameEntities->resetGame();
        changeScene(START);
        break;
    default:
        break;
    }
}