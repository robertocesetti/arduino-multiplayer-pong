#include "src/game-engine.h"

GameEngine* gameEngine;

// TODO: communication, score, scenes (win / loose / start), borders (L/R), ball skew
// TODO: FReeRTOS auto configure

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino Multiplayer Pong");

  gameEngine = new GameEngine();
  gameEngine->start();

}

void loop() {}

/*
Interfaces:
  - GameEngine
    - start
    - gameLoop
    - end

  - RenderEngine
    - render (OLED)

  - NetworkManager
    - receiveData
    - sendData

  - UserManager
    - userInput

Structures:
  - Ball {
      positionX,
      positionY,
      velocityX,
      velocityY,
      RADIUS
    }
  - Paddle {
      POSITION_X,
      positionY,
      velocityY,
      HEIGHT,
      WIDTH
    }

  - BallMessage {
      positionX,
      positionY,
      velocityX
    }

  - PaddleMessage {
      positionY
    }

  - ScoreMessage {
      score1,
      score2

      // OR score as char[]
    }

  - OR: Message {
    messageType,
    data,
  }


Enums:
  - MessageType: {
    BALL, PADDLE, SCORE
  }

  - SceneType: {
    START, GAME, END
  }

|--------------------------|
|                          |
|  |                       |
|             o            |
|                        | |
|                          |
|--------------------------|


*/