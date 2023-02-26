#include <Arduino.h>
#include "render-engine.h"
#include "gameEntities/game-entity.h"
#include "game-task-manager.h"

RenderEngine::RenderEngine() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), currentScene(nullptr)
{
    initDisplayProperties();
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::initDisplayProperties()
{
    // initialize the OLED object
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    // clear the display
    display.clearDisplay();

    displayProperties = new DisplayProperties;
    displayProperties->width = SCREEN_WIDTH;
    displayProperties->height = SCREEN_HEIGHT;

    displayProperties->topLeftX = 0;
    displayProperties->topLeftY = 0;

    displayProperties->topRightX = SCREEN_WIDTH - 1;
    displayProperties->topRightY = 0;

    displayProperties->bottomLeftX = 0;
    displayProperties->bottomLeftY = SCREEN_HEIGHT - 1;

    displayProperties->bottomRightX = SCREEN_WIDTH - 1;
    displayProperties->bottomRightY = SCREEN_HEIGHT - 1;
}

void RenderEngine::render()
{
    int fps = 0;
    unsigned long lastTime = millis();

    while (true)
    {
        fps++;
        if (millis() > lastTime + 1000)
        {
            Serial.printf("FPS: %i\n", fps);
            lastTime = millis();
            fps = 0;
        }

        display.clearDisplay();
        if (currentScene != nullptr)
            currentScene->render();
        display.display();

        if(currentScene != nullptr && currentScene->renderOnce()){
            vTaskSuspend(NULL);
        }
    }
}

void RenderEngine::changeScene(Scene *scene)
{
    scene->initialize(&display, displayProperties);
    currentScene = scene;
    vTaskResume(GameTaskManager::getInstance()->getRenderTaskHandler());
}