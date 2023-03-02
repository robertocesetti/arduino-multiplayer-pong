#include <Arduino.h>
#include "game-task-manager.h"

// Initialize the static instance variable to null
GameTaskManager *GameTaskManager::instance = nullptr;

GameTaskManager *GameTaskManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameTaskManager();
    }
    return instance;
}

void GameTaskManager::printTasksStatus()
{
    Serial.printf("Status of %s: %s\n", pcTaskGetName(tasks.inputTaskHandler), STATE_NAMES[eTaskGetState(tasks.inputTaskHandler)]);
    Serial.printf("Status of %s: %s\n", pcTaskGetName(tasks.gameLoopTaskHandler), STATE_NAMES[eTaskGetState(tasks.gameLoopTaskHandler)]);
    Serial.printf("Status of %s: %s\n", pcTaskGetName(tasks.networkTaskHandler), STATE_NAMES[eTaskGetState(tasks.networkTaskHandler)]);
    Serial.printf("Status of %s: %s\n", pcTaskGetName(tasks.renderTaskHandler), STATE_NAMES[eTaskGetState(tasks.renderTaskHandler)]);
    Serial.printf("Status of %s: %s\n", pcTaskGetName(tasks.statusTaskHandler), STATE_NAMES[eTaskGetState(tasks.statusTaskHandler)]);
}

void GameTaskManager::networkQueueSend(Message *message)
{
    /* Send a pointer to a struct AMessage object to the queue referenced by
    the xQueue variable. Don't block if the queue is already full (the third
    parameter to xQueueSend() is zero, so not block time is specified). */

    xQueueSendToBack(tasks.networkQueueHandler, (void *)&message, 0);
    Serial.printf("Adding message to queue - messageType %i, queue space %i\n", message->messageType, uxQueueSpacesAvailable(tasks.networkQueueHandler));
}

// Define the global GameTaskManagerInstance variable
GameTaskManager *GameTaskManagerInstance = GameTaskManager::getInstance();