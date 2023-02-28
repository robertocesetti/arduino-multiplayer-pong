#include "network-manager.h"
#include "WiFi.h"
#include <esp_wifi.h>

NetworkManager *NetworkManager::instance = nullptr;

NetworkManager::NetworkManager() : initialized(false)
{
    WiFi.mode(WIFI_STA); // ESP32 in Station Mode
    uint64_t mac = ESP.getEfuseMac();
    uint8_t macArray[6];
    for (int i = 0; i < 6; i++)
    {
        macArray[i] = (mac >> ((5 - i) * 8)) & 0xFF;
    }

    if (memcmp(macArray, U_MAC_1, 6) == 0)
    {
        Serial.println("\nI'm Master\n");
        // esp_wifi_set_mac(WIFI_IF_STA, L_MAC_1);
        master = true;
    }
    else if (memcmp(macArray, U_MAC_2, 6) == 0)
    {
        Serial.println("\nI'm Slave\n");
        // esp_wifi_set_mac(WIFI_IF_STA, L_MAC_2);
        master = false;
    }

    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

    if (master)
    {
        uint8_t broadcastAddressTmp[6] = {L_MAC_2[0], L_MAC_2[1], L_MAC_2[2], L_MAC_2[3], L_MAC_2[4], L_MAC_2[5]};
        // broadcastAddress = {0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84};
        memcpy(broadcastAddress, broadcastAddressTmp, 6);
    }
    else
    {
        uint8_t broadcastAddressTmp[6] = {L_MAC_1[0], L_MAC_1[1], L_MAC_1[2], L_MAC_1[3], L_MAC_1[4], L_MAC_1[5]};
        // broadcastAddress = {0x78, 0x21, 0x84, 0xDE, 0x08, 0x58};
        memcpy(broadcastAddress, broadcastAddressTmp, 6);
    }

    WiFi.disconnect();
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::broadcast(const String &message)
// Emulates a broadcast
{
    esp_now_peer_info_t peerInfo = {};
    uint8_t broadcastAddressTmp[6];// ={0x78, 0x21, 0x84, 0xDE, 0x08, 0x58};
    
    if (master)
    {
        auto init = std::initializer_list<uint8_t>({0x78, 0x21, 0x84, 0xDE, 0x08, 0x58});
        std::copy(init.begin(), init.end(), broadcastAddressTmp);
    }
    else
    {
        auto init = std::initializer_list<uint8_t>({0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84});
        std::copy(init.begin(), init.end(), broadcastAddressTmp);
    }
    memcpy(&peerInfo.peer_addr, broadcastAddressTmp, 6);

    // Serial.println(broadcastAddress);
    if (!esp_now_is_peer_exist(broadcastAddressTmp))
    {
        esp_now_add_peer(&peerInfo);
    }
    // Send message
    esp_err_t result = esp_now_send(broadcastAddressTmp, (const uint8_t *)message.c_str(), message.length());

    // Print results to serial monitor
    checkRes(result);
}

void NetworkManager::startCommunication()
{
    while (true)
    {
        if (!initialized)
        {
            Serial.println("Inizialization failed!");
            vTaskSuspend(NULL);
            continue;
        }

        // Send message
        // esp_err_t result = esp_now_send(getOtherMAC(), (const uint8_t *)message.c_str(), message.length());
        broadcast("ciao");

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

void NetworkManager::initialize()
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

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted paket
    esp_now_register_send_cb(onDataSent);

    Serial.println("after esp_now_register_send_cb");

    // uint8_t mac[] = {0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84};
    // esp_now_peer_info_t pInfo;

    //if (!instance->addPeer())
    //  return;

    //  Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(onDataRecv);

    Serial.println("after esp_now_register_recv_cb");

    instance->initialized = true;
}

bool NetworkManager::addPeer()
{
    peerInfo = {};
    // Register peer
    memcpy(peerInfo.peer_addr, getOtherMAC(), 6);
    /*
    for (int ii = 0; ii < 6; ++ii)
    {
        pInfo.peer_addr[ii] = (uint8_t)mac[ii];
    }*/
    peerInfo.ifidx = WIFI_IF_AP;
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // print the MAC address in hexadecimal notation
    Serial.print("MAC address: ");
    for (int i = 0; i < 6; i++)
    {
        Serial.print(peerInfo.peer_addr[i], HEX);
        if (i < 5)
            Serial.print(":");
    }
    Serial.println();
    esp_err_t addStatus = esp_now_add_peer(&peerInfo);
    return checkRes(addStatus);
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
    Serial.print("Last Packet Sent to: ");
    Serial.println(macStr);
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void NetworkManager::onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    // Only allow a maximum of 250 characters in the message + a null terminating byte
    char buffer[ESP_NOW_MAX_DATA_LEN + 1];
    int msgLen = min(ESP_NOW_MAX_DATA_LEN, data_len);
    strncpy(buffer, (const char *)data, msgLen);

    // Make sure we are null terminated
    buffer[msgLen] = 0;

    // Format the MAC address
    char macStr[18];
    formatMacAddress(mac_addr, macStr, 18);

    // Send Debug log message to the serial port
    Serial.printf("Received message from: %s - %s\n", macStr, buffer);
}

bool NetworkManager::checkRes(esp_err_t addStatus)
{
    if (addStatus == ESP_OK)
    {
        // Pair success
        Serial.println("Pair success");
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
