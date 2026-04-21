#pragma once

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include "esp_log.h"
#include "constants.h"
#include <ArduinoJson.h>

namespace spi_ffs
{
    /**
     * @brief Verify if the configuration file exists in SPIFFS.
     *
     * @return true if the settings file is present.
     * @return false if the file is missing or SPIFFS cannot mount.
     */
    bool settingsFileExists();

    /**
     * @brief Create or overwrite the configuration file in SPIFFS.
     *
     * @param conteudo JSON content to save.
     * @return true if the file was written successfully.
     * @return false if the write operation failed.
     */
    bool createFile(const char *conteudo);

    /**
     * @brief Read the device configuration JSON from SPIFFS.
     *
     * @param doc Output JSON document to fill with parsed configuration.
     * @return true if the file was read and parsed successfully.
     * @return false if the file is missing or parsing fails.
     */
    bool readConfigFile(StaticJsonDocument<1024> &doc);
}
