#pragma once

#include "spiffs_utils.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "esp_log.h"

namespace web_server_esp
{
    /**
     * @brief Initialize the asynchronous web server for configuration.
     *
     * @details
     * Sets up HTTP routes and captive portal handling so users can configure
     * WiFi, MQTT, and sensor parameters via the browser.
     */
    void initWebServer();
}
