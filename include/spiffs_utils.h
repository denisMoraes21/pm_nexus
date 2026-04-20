#pragma once

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include "esp_log.h"
#include "constants.h"
#include <ArduinoJson.h>

namespace spi_ffs
{
    bool settingsFileExists();
    bool createFile(const char *conteudo);
    bool readConfigFile(StaticJsonDocument<1024> &doc);
}
