#include <Arduino.h>
//#include <Arduino_FreeRTOS.h>
#include "input-manager.h"

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

            switch (sceneManager->getCurrentScene())
            {
            case START:
            case PAUSE:
                sceneManager->changeScene(GAME);
                break;
            case GAME:
                sceneManager->changeScene(PAUSE);
                break;
            case SCORE:
                sceneManager->changeScene(START);
                break;
            default:
                break;
            }
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

        paddle2->updateVelocity(0, velocityY);

        btn_prev = digitalRead(SEL);
        vTaskDelay(pdMS_TO_TICKS(50)); // TODO 10
    }
}
