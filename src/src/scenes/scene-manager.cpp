#include <Arduino.h>
#include "scene-manager.h"
#include "start-scene.h"
#include "game-scene.h"
#include "final-score-scene.h"
#include "pause-scene.h"
#include "waiting-scene.h"
#include "connection-scene.h"
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
    auto ws = new WaitingScene();
    auto cs = new ConnectionScene();

    scenes[0] = gs;
    scenes[1] = fs;
    scenes[2] = ss;
    scenes[3] = ps;
    scenes[4] = ws;
    scenes[5] = cs;

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

void SceneManager::setReady(bool r)
{
    ready = r;
    // checkReadyState();
}

void SceneManager::setReady2(bool r)
{
    ready2 = r;
    checkReadyState();
}

void SceneManager::checkReadyState()
{
    Serial.printf("Status Players: P1: %i -- P2: %i\n", ready, ready2);
    if (ready && ready2 && getCurrentScene() == WAITING)
    {
        changeScene();
    }
}

void SceneManager::changeScene()
{
    switch (getCurrentScene())
    {
    case START:
        setReady(true);
        changeScene(WAITING);
        rm.ready = true;
        GameTaskManager::getInstance()->networkQueueSend(&rm);
        break;
    case WAITING:
        if (!ready || !ready2)
            break;
        ready = false;
        ready2 = false;
        changeScene(GAME);
        sm.sceneType = GAME;
        GameTaskManager::getInstance()->networkQueueSend(&sm);
        break;
    case PAUSE:
        changeScene(GAME);
        sm.sceneType = GAME;
        GameTaskManager::getInstance()->networkQueueSend(&sm);
        break;
    case GAME:
        changeScene(PAUSE);
        sm.sceneType = PAUSE;
        GameTaskManager::getInstance()->networkQueueSend(&sm);
        break;
    case SCORE:
        restart();
        break;
    default:
        break;
    }
}

void SceneManager::restart()
{
    gameEntities->resetGame();
    changeScene(START);
    ready = false;
    ready2 = false;
}