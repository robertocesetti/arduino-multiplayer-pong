#pragma once

#include "../gameEntities/game-entity.h"
#include "scene.h"


class GameScene : public Scene
{
    private:
        GameEntity* gameEntities;
        
        void drawBorder();
        void drawBall();
        void drawPaddle(Paddle *paddle);
    
    public:
        GameScene(GameEntity* gameEntities);
        ~GameScene();

        void render() override;
};