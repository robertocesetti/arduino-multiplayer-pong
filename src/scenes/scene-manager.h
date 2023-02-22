#pragma once

#include "scene.h"
#include "../gameEntities/game-entity.h"
#include "../render-engine.h"

const static int SCENE_NUMBER = 4;

class SceneManager
{
private:
    Scene* scenes[SCENE_NUMBER];
    GameEntity* gameEntities;
    RenderEngine* renderEngine;

    void createScenes();

public:
    SceneManager(GameEntity* gameEntities, RenderEngine* renderEngine);
    ~SceneManager();

    void changeScene(SceneType sceneType);
    
    SceneType getCurrentScene(){
        return renderEngine->getCurrentScene()->getSceneType();
    }
};
