#include "src/game-engine.h"

GameEngine gameEngine;


void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino Multiplayer Pong");

  gameEngine.start();
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