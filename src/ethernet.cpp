#include "ethernet.h"

byte mac[6];

void ethernet::generateMAC(byte mac[6])
{
    uint32_t chipId = ESP.getEfuseMac();

    mac[0] = 0x02;
    mac[1] = (chipId >> 24) & 0xFF;
    mac[2] = (chipId >> 16) & 0xFF;
    mac[3] = (chipId >> 8) & 0xFF;
    mac[4] = chipId & 0xFF;
    mac[5] = random(0, 255); // New mac to shield ethernet
}

void ethernet::checkEthetnet()
{
    const char *TAG = "ETHERNET";
    generateMAC(mac);
    if (Ethernet.begin(mac) == 0)
    {

#ifdef DEBUG_VALUES
        ESP_LOGI(TAG, "Fail during setting Ethernet via DHCP");
#endif

        ESP.restart();
        return;
    }

#ifdef DEBUG_VALUES
    ESP_LOGI(TAG, "Ethernet initialized!");
#endif
}
