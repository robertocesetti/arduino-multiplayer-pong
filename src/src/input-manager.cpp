#include <Arduino.h>
#include "input-manager.h"
#include "network-manager.h"

InputManager::InputManager(SceneManager *sm) : sceneManager(sm)
{
    pinMode(VERT, INPUT);
    pinMode(HORZ, INPUT);
    pinMode(SEL, INPUT_PULLUP);
}

InputManager::~InputManager()
{
}

void InputManager::startReading(GameEntity *gameEntities)
{
    Paddle *paddle1 = gameEntities->getPaddle1();
    Paddle *paddle2 = gameEntities->getPaddle2();
    int vertical;
    int velocityY;

    uint8_t btn_prev;
    uint8_t btn;

    bool inGame = false;

    while (true)
    {
        btn = digitalRead(SEL);
        if (btn == LOW && btn_prev == HIGH)
        {
            Serial.println("button pressed");
            sceneManager->changeScene();
        }

        vertical = analogRead(VERT);
        velocityY = 0;
        if (vertical > 3500)
        {
            velocityY = -2;
        }
        else if (vertical < 1000)
        {
            velocityY = 2;
        }

        if (NetworkManager::getInstance()->isMaster())
            paddle2->updateVelocity(0, velocityY);
        else
            paddle1->updateVelocity(0, velocityY);

        btn_prev = digitalRead(SEL);
        vTaskDelay(pdMS_TO_TICKS(50)); // TODO 10
    }
}
