#include "wifi_utils.h"

const char *TAG_STA = "WiFi-STA";
const char *TAG_AP = "WiFi-AP";

void wifi::connectWiFi(WiFiParameters wifi_data)
{

    const char *SSID_STA = wifi_data.SSID_STA;
    const char *PASSWORD_STA = wifi_data.PASSWORD_STA;
    const int try_connection_ = wifi_data.TRY_CONNECTION;

#ifndef DEBUG_LEVEL
    ESP_LOGI(TAG_STA, "Wi-Fi Connection...");
    ESP_LOGI(TAG_STA, "SSID: %s, PASSSWORD: %s", SSID_STA, PASSWORD_STA);
#endif

    WiFi.mode(WIFI_OFF);
    WiFi.disconnect();

    delay(1000);

    WiFi.mode(WIFI_STA);
    delay(1000);
    ESP_LOGI(TAG_STA, "%s, %s", SSID_STA, PASSWORD_STA);
    WiFi.begin(SSID_STA, PASSWORD_STA);

    int try_connection = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);

#ifndef DEBUG_LEVEL
        ESP_LOGI(TAG_STA, "Connecting ...");
#endif

        try_connection++;
        if (try_connection > try_connection_)
        {

#ifndef DEBUG_LEVEL
            ESP_LOGE(TAG_STA, "Error during Wi-Fi connection. Restarting...");
#endif

            ESP.restart();
        }
    }

#ifndef DEBUG_LEVEL
    ESP_LOGI(TAG_STA, "Wi-Fi Connected! IP: %s ", WiFi.localIP().toString());
#endif
}

void wifi::startAccessPoint()
{
#ifndef DEBUG_LEVEL
    ESP_LOGI(TAG_AP, "Starting Access Point...");
    ESP_LOGI(TAG_AP, "SSID: %s, PASSWORD: ********", SSID_AP);
#endif

    WiFi.mode(WIFI_AP);
    WiFi.softAP(SSID_AP, PASSWORD_AP);

    IPAddress ip = WiFi.softAPIP();

#ifndef DEBUG_LEVEL
    ESP_LOGI(TAG_AP, "AP Started!");
    ESP_LOGI(TAG_AP, "IP: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
#endif
}
