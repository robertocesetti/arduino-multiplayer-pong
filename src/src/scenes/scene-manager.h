#pragma once

#include "scene.h"
#include "../gameEntities/game-entity.h"
#include "../render-engine.h"
#include "../game-loop.h"

const static int SCENE_NUMBER = 4;

class SceneManager
{
private:
    Scene* scenes[SCENE_NUMBER];
    GameEntity* gameEntities;
    RenderEngine* renderEngine;
    GameLoop* gameLoop;

    void createScenes();

public:
    SceneManager(GameEntity* gameEntities, RenderEngine* renderEngine, GameLoop *gl);
    ~SceneManager();

    void changeScene(SceneType sceneType);
    
    SceneType getCurrentScene(){
        return renderEngine->getCurrentScene()->getSceneType();
    }
};
