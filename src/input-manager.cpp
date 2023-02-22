#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "input-manager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::startReading(GameEntity *gameEntities)
{
    Paddle *paddle2 = gameEntities->getPaddle2();
    int vertical;
    int velocityY;
    while (true)
    {
        vertical = analogRead(VERT);
        velocityY = 0;
        if (vertical > 700)
        {
            velocityY = -2;
        }
        else if (vertical < 300)
        {
            velocityY = 2;
        }

        paddle2->updateVelocity(0, velocityY);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
