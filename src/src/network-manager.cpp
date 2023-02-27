#include "network-manager.h"
#include "WiFi.h"

NetworkManager *NetworkManager::instance = nullptr;

NetworkManager::NetworkManager()
{
    WiFi.mode(WIFI_MODE_STA);
    myMAC = WiFi.macAddress();
    master = strcmp(stringify(MAC_1), myMAC.c_str()) == 0;

    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", myMAC[0], myMAC[1], myMAC[2], myMAC[3], myMAC[4], myMAC[5]);
    Serial.printf("My MAC address: %s, Am I the master? %s\n", macStr, (master ? "yes" : "no"));
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::startCommunication()
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
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

void NetworkManager::initialize(void)
{
    instance = getInstance();

    if (instance->initialized)
        return;

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted paket
    esp_now_register_send_cb(onDataSent);

    // Register peer
    memcpy(instance->peerInfo.peer_addr, instance->getOtherMAC(), 6);
    instance->peerInfo.channel = 0;
    instance->peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&(instance->peerInfo)) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }

    //  Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(onDataRecv);

    instance->initialized = true;
}

// Callback when data is sent
void NetworkManager::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    if (status == 0)
    {
        // success = "Delivery Success :)";
    }
    else
    {
        // success = "Delivery Fail :(";
    }
}

// Callback when data is received
void NetworkManager::onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    // memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
    Serial.print("Bytes received: ");
    Serial.println(data_len);
    // incomingTemp = incomingReadings.temp;
    // incomingHum = incomingReadings.hum;
    // incomingPres = incomingReadings.pres;
}