#include <Arduino.h>
#include "scene-manager.h"
#include "start-scene.h"
#include "game-scene.h"
#include "final-score-scene.h"
#include "pause-scene.h"

SceneManager::SceneManager(GameEntity *ge, RenderEngine *re) : gameEntities(ge), renderEngine(re)
{
    createScenes();
    changeScene(START);
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

    Serial.print(gs->getSceneType());
    Serial.print(fs->getSceneType());
    Serial.print(ss->getSceneType());
    Serial.print(ps->getSceneType());

    scenes[0] = gs;
    scenes[1] = fs;
    scenes[2] = ss;
    scenes[3] = ps;

    for (Scene *scene : scenes)
    {
        Serial.println(scene->getSceneType());
    }
}

void SceneManager::changeScene(SceneType sceneType)
{
    for (Scene *scene : scenes)
    {
        if (scene->getSceneType() == sceneType)
        {
            renderEngine->changeScene(scene);
            //Serial.println(scene->getSceneType());
            return;
        }
    }
}