#pragma once

#include <esp_now.h>
#include "BluetoothSerial.h"

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

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
const uint8_t MAC_2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

class NetworkManager
{
private:
    BluetoothSerial serialBT;
    String myMAC;
    esp_now_peer_info_t peerInfo;

    //esp_now_send_cb_t onDataReceive = onDataRecv; 

    bool master;

public:
    NetworkManager();
    ~NetworkManager();

    void initialize(void);
    void receiveData();
    void sendData(void *data);

    bool isMaster() { return master; }
    bool isSlave() { return !master; }
    const uint8_t *getOtherMAC() { return master ? MAC_2 : MAC_1; };

    void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
};