#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "messages/scene-message.h"

struct GameTaskManagerStruct
{
    TaskHandle_t gameLoopTaskHandler;
    TaskHandle_t renderTaskHandler;
    TaskHandle_t inputTaskHandler;
    TaskHandle_t networkTaskHandler;
    TaskHandle_t statusTaskHandler;
    QueueHandle_t networkQueueHandler;
};

const String STATE_NAMES[] = {"eRunning", "eReady", "eBlocked", "eSuspended", "eDeleted", "eInvalid"};

class GameTaskManager
{
private:
    static GameTaskManager *instance;
    GameTaskManager(){};

public:
    GameTaskManagerStruct tasks;
    static GameTaskManager *getInstance();

    void printTasksStatus();
    void networkQueueSend(Message *message);
};

// Declare instance as a global variable, with external linkage
extern GameTaskManager *GameTaskManagerInstance;