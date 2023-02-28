#include "network-manager.h"
#include "WiFi.h"
#include <esp_wifi.h>

NetworkManager *NetworkManager::instance = nullptr;

NetworkManager::NetworkManager() : initialized(false)
{
    // Set your new MAC Address
    // uint8_t CustomMACaddress[] = {0x78, 0x21, 0x84, 0xE3, 0x80, 0x97};

    WiFi.mode(WIFI_STA); // ESP32 in Station Mode
    uint64_t mac = ESP.getEfuseMac();
    uint8_t macArray[6];
    for (int i = 0; i < 6; i++)
    {
        macArray[i] = (mac >> ((5 - i) * 8)) & 0xFF;
    }

    esp_wifi_set_mac(WIFI_IF_STA, macArray);
    myMAC = WiFi.macAddress();
    Serial.println(WiFi.macAddress());

    /*
    Serial.print("Default ESP32 Board MAC Address:  ");
    //Prints default MAC address
    Serial.println(WiFi.macAddress());
    esp_wifi_set_mac(WIFI_IF_STA, &CustomMACaddress[0]);
    Serial.print("Custom MAC Address for ESP32:  ");
    //Prints Custom MAC address
    Serial.println(WiFi.macAddress());
    master = strcmp(stringify(MAC_1), myMAC.c_str()) == 0;
    */
}

NetworkManager::~NetworkManager()
{
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
        // Set values to send
        BME280Readings.temp = 1;
        BME280Readings.hum = 1;
        BME280Readings.pres = 1;
        // Send message via ESP-NOW
        esp_err_t result = esp_now_send(getOtherMAC(), (uint8_t *)&BME280Readings, sizeof(BME280Readings));

        if (result == ESP_OK)
        {
            Serial.println("Sent with success");
        }
        else
        {
            Serial.println("Error sending the data");
        }
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
        return;
    }
    Serial.println("ESP NOW INIT");

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted paket
    esp_now_register_send_cb(onDataSent);

    Serial.println("after esp_now_register_send_cb");

    // uint8_t mac[] = {0x78, 0x21, 0x84, 0xDD, 0xF2, 0x84};
    // esp_now_peer_info_t pInfo;

    if(!instance->addPeer()) return;

    //  Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(onDataRecv);

    Serial.println("after esp_now_register_recv_cb");

    instance->initialized = true;
}

bool NetworkManager::addPeer()
{
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
    if (addStatus == ESP_OK)
    {
        // Pair success
        Serial.println("Pair success");
    }
    else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT)
    {
        // How did we get so far!!
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