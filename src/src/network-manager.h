#pragma once

#include <esp_now.h>
#include <Arduino.h>

#define stringify(x) #x

typedef struct struct_message
{
    float temp;
    float hum;
    float pres;
} struct_message;

// Master
const uint8_t MAC_1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Slave
const uint8_t MAC_2[] = {0x37, 0x38, 0x3A, 0x32, 0x31, 0x3A};

class NetworkManager
{
private:
    static NetworkManager *instance;

    String myMAC;
    esp_now_peer_info_t peerInfo;
    bool master;
    bool initialized;

    NetworkManager();

public:
    ~NetworkManager();

    bool isMaster() { return master; }
    bool isSlave() { return !master; }
    const uint8_t *getOtherMAC() { return master ? MAC_2 : MAC_1; };

    void startCommunication();

    static NetworkManager* getInstance();
    static void initialize();
    static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
};