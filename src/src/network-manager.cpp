#include "network-manager.h"
#include "WiFi.h"

#include "BluetoothSerial.h"

NetworkManager::NetworkManager()
{
    WiFi.mode(WIFI_MODE_STA);
    myMAC = WiFi.macAddress();
    master = strcmp(stringify(MAC_1), myMAC.c_str()) == 0;
    if (master)
    {
        serialBT.begin("ESP32-master");
    }
    else
    {
        serialBT.begin("ESP32-slave");
    }
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::initialize(void)
{
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted paket
    // esp_now_register_send_cb(onDataRecv);

    // Register peer
    memcpy(peerInfo.peer_addr, getOtherMAC(), 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }

    //  Register for a callback function that will be called when data is received
    //esp_now_register_recv_cb(onDataRecv);
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

void NetworkManager::receiveData(void)
{
    while (true)
    {
        if (serialBT.available())
        {
            Serial.print("From BT: ");
            Serial.println(serialBT.read());
            sendData(nullptr);
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void NetworkManager::sendData(void *data)
{
    serialBT.write('a');
}