#pragma once

#include "scene.h"
#include "../gameEntities/game-entity.h"
#include "../render-engine.h"
#include "../game-loop.h"
#include "../messages/scene-message.h"
#include "../messages/ready-message.h"

const static int SCENE_NUMBER = 6;

class SceneManager
{
private:
    Scene* scenes[SCENE_NUMBER];
    GameEntity* gameEntities;
    RenderEngine* renderEngine;
    GameLoop* gameLoop;
    SceneMessage sm;
    ReadyMessage rm;
    bool ready = false;
    bool ready2 = false;

    void createScenes();
    void checkReadyState();

public:
    SceneManager(GameEntity* gameEntities, RenderEngine* renderEngine, GameLoop *gl);
    ~SceneManager();

    void changeScene(SceneType sceneType);
    void changeScene();    
    bool isReady() { return ready; }
    void setReady(bool r);
    void setReady2(bool r);
    void restart();
    
    SceneType getCurrentScene(){
        return renderEngine->getCurrentScene()->getSceneType();
    }
};
