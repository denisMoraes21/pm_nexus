#include "wifi_utils.h"

void wifi::connectWiFi()
{
    const char *TAG = "Wi-Fi";
    ESP_LOGI(TAG, "Wi-Fi Connection...");
    ESP_LOGI(TAG, "SSID: %s, PASSSWORD: %s", ssid_sta, password_sta);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    WiFi.begin(ssid_sta, password_sta);

    int try_connection = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        ESP_LOGI(TAG, "Connecting ...");
        try_connection++;
        if (try_connection > try_connection_seconds)
        {
            ESP_LOGE(TAG, "Error during Wi-Fi connection. Restarting...");
            ESP.restart();
        }
    }

    ESP_LOGI(TAG, "Wi-Fi Connected! IP: %s ", WiFi.localIP().toString());
}

void wifi::startAccessPoint()
{
    const char *TAG = "WiFi-AP";

    ESP_LOGI(TAG, "Starting Access Point...");
    ESP_LOGI(TAG, "SSID: %s, PASSWORD: %s", ssid_ap, password_ap);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid_ap, password_ap);

    IPAddress ip = WiFi.softAPIP();

    ESP_LOGI(TAG, "AP Started!");
    ESP_LOGI(TAG, "IP: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}
