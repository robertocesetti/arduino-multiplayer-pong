#include <Arduino_FreeRTOS.h>
#include "src/game-engine.h"

GameEngine gameEngine{};

void MainTask(void *parmas);

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino Multiplayer Pong");

  xTaskCreate(MainTask, "MainTask", 1024, NULL, 1, NULL);
}

void MainTask(void *parmas)
{
  int i = 1;
  while (i)
  {
    Serial.println("MainTask called");
    //Serial.println(gameEngine.isRunning());
    //gameEngine.start();
    vTaskDelay(pdMS_TO_TICKS(500));
    //i = 0;
  }
  // 

  vTaskDelete(NULL);
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