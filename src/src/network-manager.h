#pragma once

#include <esp_now.h>
#include <Arduino.h>
#include "gameEntities/game-entity.h"

#define stringify(x) #x

typedef struct struct_message
{
    float temp;
    float hum;
    float pres;
} struct_message;

// dam: 84 f2 dd 84 21 78 - 0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84
// mat: 58 08 de 84 21 78 - 0x78, 0x21, 0x84, 0xDE, 0x08, 0x58
// default mac: 0x37, 0x38, 0x3A, 0x32, 0x31, 0x3A

// Master
const uint8_t U_MAC_1[] = {0x84, 0xF2, 0xDD, 0x84, 0x21, 0x78};
const uint8_t L_MAC_1[] = {0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84};

// Slave
const uint8_t U_MAC_2[] = {0x58, 0x08, 0xDE, 0x84, 0x21, 0x78};
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
    struct_message BME280Readings;
    GameEntity *gameEntity;

    bool addPeer();
    bool checkRes(esp_err_t addStatus);

    void broadcast(const String &message);

    NetworkManager();

public:
    ~NetworkManager();

    bool isMaster() { return master; }
    bool isSlave() { return !master; }
    const uint8_t *getOtherMAC() { return master ? L_MAC_2 : L_MAC_1; };

    void startCommunication();

    static NetworkManager* getInstance();
    static void initialize(GameEntity *gameEntity);
    static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
};