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

const long MILLIS_TIMEOUT = 5000; 
const long RECONNECT_DELAY = 2000;
const long ESP_INIT_RETRY = 5000;

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
    unsigned long lastReceivedPacketTime;    
    String log;
    bool connected;

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
    bool isConnected() { return connected; }
    void startCommunication();
    Paddle *getMyPaddle() { return master ? gameEntity->getPaddle2() : gameEntity->getPaddle1(); };
    String getLog() {return log;}
    void setLog(String newLog) {log = newLog;}

    static NetworkManager *getInstance();
    static bool initialize(GameEntity *gameEntity, SceneManager *sceneManager);
    static void checkConnection();
};