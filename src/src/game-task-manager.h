#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

struct GameTaskManagerTest
{
    TaskHandle_t gameLoopTaskHandler;
    TaskHandle_t renderTaskHandler;
    TaskHandle_t inputTaskHandler;
    TaskHandle_t networkTaskHandler;
};

class GameTaskManager
{
private:
    static GameTaskManager *instance;
    GameTaskManager(){};

public:
    GameTaskManagerTest tasks;
    static GameTaskManager *getInstance();
};

// Declare instance as a global variable, with external linkage
extern GameTaskManager *GameTaskManagerInstance;