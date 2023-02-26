#include "game-task-manager.h"

// Initialize the static instance variable to null
GameTaskManager* GameTaskManager::instance = nullptr;

GameTaskManager *GameTaskManager::getInstance() {
    if (instance == nullptr) {
        instance = new GameTaskManager();
    }
    return instance;
}

TaskHandle_t* GameTaskManager::getGameLoopTaskHandler() {
    return &gameLoopTaskHandler;
}

TaskHandle_t* GameTaskManager::getRenderTaskHandler() {
    return &renderTaskHandler;
}

TaskHandle_t* GameTaskManager::getInputTaskHandler() {
    return &inputTaskHandler;
}

TaskHandle_t* GameTaskManager::getNetworkTaskHandler() {
    return &networkTaskHandler;
}

// Define the global GameTaskManagerInstance variable
GameTaskManager* GameTaskManagerInstance = GameTaskManager::getInstance();