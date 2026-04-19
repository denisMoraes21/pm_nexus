#pragma once

#include "spiffs_utils.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "esp_log.h"

namespace web_server_esp
{
    void initWebServer();
}
