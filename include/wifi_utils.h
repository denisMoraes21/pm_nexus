// Bibliotecas externas == /lib
#include <PubSubClient.h>
#include <WiFi.h>
#include <esp_log.h>

// Módulos do projeto == /include
#include "constants.h"

namespace wifi
{
    void connectWiFi();
    void startAccessPoint();
}
