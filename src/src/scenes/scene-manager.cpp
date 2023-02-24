#include <Arduino.h>
#include "scene-manager.h"
#include "start-scene.h"
#include "game-scene.h"
#include "final-score-scene.h"
#include "pause-scene.h"

SceneManager::SceneManager(GameEntity *ge, RenderEngine *re): gameEntities(ge), renderEngine(re)
{
    createScenes();
}

SceneManager::~SceneManager()
{
}

void SceneManager::createScenes()
{
    auto gs = new GameScene(gameEntities);
    auto fs = new FinalScoreScene();
    auto ss = new StartScene();
    auto ps = new PauseScene();

    scenes[0] = gs;
    scenes[1] = fs;
    scenes[2] = ss;
    scenes[3] = ps;

    Serial.print("Scene loaded:");
    for (Scene *scene : scenes)
    {
        Serial.print(" ");
        Serial.print(scene->getSceneType());
    }
    Serial.print("\n");
}

void SceneManager::changeScene(SceneType sceneType)
{
    for (Scene *scene : scenes)
    {
        if (scene->getSceneType() == sceneType)
        {
            Serial.print("Change Scene: ");
            Serial.println(scene->getSceneType());
            renderEngine->changeScene(scene);
            return;
        }
    }
}