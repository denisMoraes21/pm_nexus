// Bibliotecas externas == /lib
#include <PubSubClient.h>
#include <WiFi.h>
#include <esp_log.h>

// Módulos do projeto == /include
#include "constants.h"

struct WiFiParameters
{
    const char *SSID_STA;
    const char *PASSWORD_STA;
    int TRY_CONNECTION;
};

namespace wifi
{
    void connectWiFi(WiFiParameters wifi_data);
    void startAccessPoint();
}
