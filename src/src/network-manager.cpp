#include "network-manager.h"
#include "WiFi.h"
#include "messages/position-message.h"
#include "messages/point-message.h"
#include "messages/scene-message.h"
#include "game-task-manager.h"

#include <esp_wifi.h>

NetworkManager *NetworkManager::instance = nullptr;

NetworkManager::NetworkManager() : initialized(false)
{
    // ESP32 in Station Mode
    WiFi.mode(WIFI_STA);
    uint64_t mac = ESP.getEfuseMac();
    uint8_t macArray[6];
    for (int i = 0; i < 6; i++)
    {
        macArray[5-i] = (mac >> ((5 - i) * 8)) & 0xFF;
    }

    if (memcmp(macArray, L_MAC_1, 6) == 0)
    {
        Serial.println("\nI'm the Master\n");
        master = true;
        auto init = std::initializer_list<uint8_t>({L_MAC_2[0], L_MAC_2[1], L_MAC_2[2], L_MAC_2[3], L_MAC_2[4], L_MAC_2[5]});
        std::copy(init.begin(), init.end(), broadcastAddress);
    }
    else if (memcmp(macArray, L_MAC_2, 6) == 0)
    {
        Serial.println("\nI'm the Slave\n");
        master = false;
        auto init = std::initializer_list<uint8_t>({L_MAC_1[0], L_MAC_1[1], L_MAC_1[2], L_MAC_1[3], L_MAC_1[4], L_MAC_1[5]});
        std::copy(init.begin(), init.end(), broadcastAddress);
    }
    else
    {
        Serial.println("\nUnknow MAC address...\n");
    }

    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    WiFi.disconnect();
}

NetworkManager::~NetworkManager()
{
}

template <typename T>
void NetworkManager::sendMessage(const T &message)
{
    // Send message
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&message, sizeof(T));

    // Print results to serial monitor
    checkResult(result, "Message sent!!");
}

void NetworkManager::startCommunication()
{
    Ball *ball = gameEntity->getBall();
    /*
    Paddle *paddle1 = gameEntity->getPaddle1();
    Paddle *paddle2 = gameEntity->getPaddle2();
    */

    Paddle *paddle = getMyPaddle();

    PositionMessage positionMessage;
    PointMessage pointMessage;
    SceneMessage sm;
    Message *pxRxedMessage;

    QueueHandle_t xQueue = GameTaskManager::getInstance()->tasks.networkQueueHandler;

    while (true)
    {
        if (!initialized)
        {
            Serial.println("Inizialization failed!");
            vTaskSuspend(NULL);
            continue;
        }

        if (master)
        {
            if(ball->preparePositionMessage(&positionMessage))
                sendMessage(positionMessage);

            if(gameEntity->preparePointMessage(&pointMessage))
                sendMessage(pointMessage);
        }

        if(paddle->preparePositionMessage(&positionMessage))
            sendMessage(positionMessage);

        if (xQueueReceive(xQueue, &(pxRxedMessage), 10) == pdPASS)
        {
            Serial.printf("Received message from queue - messageType %i, queue space %i\n", pxRxedMessage->messageType, uxQueueSpacesAvailable(xQueue));
            if (pxRxedMessage->messageType == SCENE)
            {
                sm = *((SceneMessage *)pxRxedMessage);
                Serial.printf("pxRxedMessage: %p, sm: %p, st: %i\n", pxRxedMessage, &sm, sm.sceneType);
                sendMessage(sm);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(30));
    }
}

NetworkManager *NetworkManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new NetworkManager();
    }
    return instance;
}

void NetworkManager::initialize(GameEntity *gameEntity, SceneManager *sceneManager)
{
    instance = getInstance();

    if (instance->initialized)
        return;

    // Deinit ESP-NOW to ensure a clean start
    esp_now_deinit();

    Serial.println("ESP initialize");

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP.restart();
        return;
    }
    Serial.println("ESP NOW INIT");

    // Once ESPNow is successfully Init, we will register for Send CB to get the status of Trasnmitted paket
    esp_now_register_send_cb(onDataSent);

    Serial.println("after esp_now_register_send_cb");

    if (!instance->addPeer())
        return;

    //  Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(onDataRecv);

    Serial.println("after esp_now_register_recv_cb");

    instance->sceneManager = sceneManager;
    instance->gameEntity = gameEntity;
    instance->initialized = true;
}

void formatMacAddress(const uint8_t *macAddr, char *buffer, int maxLength)
// Formats MAC Address
{
    snprintf(buffer, maxLength, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
}

// Callback when data is sent
void NetworkManager::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char macStr[18];
    formatMacAddress(mac_addr, macStr, 18);
    /*Serial.print("Last Packet Sent to: ");
    Serial.println(macStr);
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");*/
}

// Callback when data is received
void NetworkManager::onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    Message receive_Data;
    memcpy(&receive_Data, data, sizeof(receive_Data));
    // Serial.printf("\nReceive Data - bytes received: %i\n", data_len);
    switch (receive_Data.messageType)
    {
    case POSITION:
    {
        PositionMessage pm;
        memcpy(&pm, data, sizeof(pm));
        unsigned int x = pm.positionX;
        unsigned int y = pm.positionY;
        // Serial.printf("Receive Data - entityType: [POSITION], positionX: %i, positionY: %i\n", x, y);
        if (pm.enityType == BALL)
        {
            instance->gameEntity->getBall()->setPosition(x, y);
        }
        else
        {
            if (instance->master)
                instance->gameEntity->getPaddle1()->setPosition(x, y);
            else
                instance->gameEntity->getPaddle2()->setPosition(x, y);
        }
    }
    break;
    case POINT:
    {
        PointMessage sm;
        memcpy(&sm, data, sizeof(sm));
        instance->gameEntity->getPaddle1()->setPoint(sm.paddle1Point);
        instance->gameEntity->getPaddle2()->setPoint(sm.paddle2Point);
    }
    break;
    case SCENE:
    {
        SceneMessage sm;
        memcpy(&sm, data, sizeof(sm));
        Serial.printf("Receive Data - messageType: [SCENE], scenetype: %i\n", sm.sceneType);
        instance->sceneManager->changeScene(sm.sceneType);
    }
    break;
    }
}

bool NetworkManager::addPeer()
{
    peerInfo = {};

    memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
    // Serial.println(broadcastAddress);
    if (!esp_now_is_peer_exist(broadcastAddress))
    {
        return checkResult(esp_now_add_peer(&peerInfo), "Pair Success!!");
    }

    return true;
}

bool NetworkManager::checkResult(esp_err_t addStatus, String success_message)
{
    if (addStatus == ESP_OK)
    {
        // Serial.println(success_message);
    }
    else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT)
    {
        Serial.println("ESPNOW Not Init");
        return false;
    }
    else if (addStatus == ESP_ERR_ESPNOW_ARG)
    {
        Serial.println("Invalid Argument");
        return false;
    }
    else if (addStatus == ESP_ERR_ESPNOW_FULL)
    {
        Serial.println("Peer list full");
        return false;
    }
    else if (addStatus == ESP_ERR_ESPNOW_NO_MEM)
    {
        Serial.println("Out of memory");
        return false;
    }
    else if (addStatus == ESP_ERR_ESPNOW_EXIST)
    {
        Serial.println("Peer Exists");
        return false;
    }
    else
    {
        Serial.println("Not sure what happened");
        return false;
    }

    return true;
}
