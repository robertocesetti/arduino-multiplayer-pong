#pragma once

#include "../gameEntities/game-entity.h"
#include "scene-manager.h"
#include "scene.h"
#include "../messages/scene-message.h"

class GameScene : public Scene
{
private:
    SceneManager* sceneManager;
    GameEntity* gameEntities;
    SceneMessage sm;

    void addPoint(Paddle *paddle);
    // void moveUsingAI(Paddle *paddle, bool godMode);

    void drawBorder();
    void drawBall();
    void drawPaddle(Paddle *paddle);
    void drawScore();

public:
    GameScene(SceneManager* sceneManager, GameEntity *gameEntities);
    ~GameScene();

    void render() override;
    void tick() override;
    bool useTick() override { return true; }
    bool renderOnce() override { return false; }
};