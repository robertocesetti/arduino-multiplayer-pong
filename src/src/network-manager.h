#pragma once

#include <esp_now.h>
#include <Arduino.h>
#include "gameEntities/game-entity.h"
#include "scenes/scene-manager.h"
#include "messages/message.h"

// Master
const uint8_t L_MAC_1[] = {0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84};

// Slave
const uint8_t L_MAC_2[] = {0x78, 0x21, 0x84, 0xDE, 0x08, 0x58};

class NetworkManager
{
private:
    static NetworkManager *instance;

    String myMAC;
    esp_now_peer_info_t peerInfo;
    bool master;
    bool initialized;
    uint8_t broadcastAddress[6];
    GameEntity *gameEntity;
    SceneManager *sceneManager;

    bool addPeer();
    bool checkResult(esp_err_t addStatus, String success_message);

    template <typename T>
    void sendMessage(const T &message);
    static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

    NetworkManager();

public:
    ~NetworkManager();

    bool isMaster() { return master; }
    bool isSlave() { return !master; }
    void startCommunication();
    Paddle *getMyPaddle() { return master ? gameEntity->getPaddle2() : gameEntity->getPaddle1(); };

    static NetworkManager *getInstance();
    static void initialize(GameEntity *gameEntity, SceneManager *sceneManager);
};