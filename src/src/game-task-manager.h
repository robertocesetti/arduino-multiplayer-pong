#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

struct GameTaskManagerTest
{
    TaskHandle_t gameLoopTaskHandler;
    TaskHandle_t renderTaskHandler;
    TaskHandle_t inputTaskHandler;
    TaskHandle_t networkTaskHandler;
    TaskHandle_t statusTaskHandler;
};

const String STATE_NAMES[] = {"eRunning", "eReady", "eBlocked", "eSuspended", "eDeleted", "eInvalid"};

class GameTaskManager
{
private:
    static GameTaskManager *instance;
    GameTaskManager(){};

public:
    GameTaskManagerTest tasks;
    static GameTaskManager *getInstance();

    void printTasksStatus();
};

// Declare instance as a global variable, with external linkage
extern GameTaskManager *GameTaskManagerInstance;