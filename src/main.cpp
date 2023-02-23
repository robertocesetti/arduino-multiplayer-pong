#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "stm32f4xx_hal.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

I2C_HandleTypeDef hi2c1; // Dichiarazione della handle della periferica I2C

void setup()
{
  Serial.begin(9600);
  // Inizializza la periferica I2C
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000; // Velocità di trasmissione I2C
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Serial.println("Gestione dell'errore di inizializzazione della periferica I2C");
    // Gestione dell'errore di inizializzazione della periferica I2C
  }
  Serial.println("Tutto Ok bro!");

  // Inizializza il display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false))
  {
    // Gestione dell'errore di inizializzazione del display OLED
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, world!");
  display.display();
  delay(1000);
  display.clearDisplay();
}

/*
#include <Arduino.h>
#include "src/game-engine.h"
#include <U8g2lib.h>
#include <U8glib-HAL.h>

GameEngine *gameEngine;

U8GLIB_SSD1306_128X64 display(U8G_I2C_OPT_NONE | U8G_I2C_OPT_FAST);

// TODO: communication, score, scenes (win / loose / start), borders (L/R), ball skew
// TODO: FReeRTOS auto configure

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino Multiplayer Pong");

  display.begin();
  // gameEngine = new GameEngine();
  // gameEngine->start();
}

void loop()
{

  display.firstPage();
  do
  {
    display.drawStr(0, 10, "Hello World!"); // write something to the internal memory				// transfer internal memory to the display
    delay(1000);
  } while (display.nextPage());
}

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