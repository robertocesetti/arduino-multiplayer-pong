#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class GameTaskManager {
private:
    TaskHandle_t gameLoopTaskHandler;
    TaskHandle_t renderTaskHandler;
    TaskHandle_t inputTaskHandler;
    TaskHandle_t networkTaskHandler;
    static GameTaskManager *instance;
    GameTaskManager() {};

public:
    static GameTaskManager *getInstance();
    TaskHandle_t* getGameLoopTaskHandler();
    TaskHandle_t* getRenderTaskHandler();
    TaskHandle_t* getInputTaskHandler();
    TaskHandle_t* getNetworkTaskHandler();
};

// Declare instance as a global variable, with external linkage
extern GameTaskManager* GameTaskManagerInstance;