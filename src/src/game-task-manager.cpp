#include "game-task-manager.h"

// Initialize the static instance variable to null
GameTaskManager* GameTaskManager::instance = nullptr;

GameTaskManager *GameTaskManager::getInstance() {
    if (instance == nullptr) {
        instance = new GameTaskManager();
    }
    return instance;
}

// Define the global GameTaskManagerInstance variable
GameTaskManager* GameTaskManagerInstance = GameTaskManager::getInstance();