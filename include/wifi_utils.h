// Bibliotecas externas == /lib
#include <PubSubClient.h>
#include <WiFi.h>
#include <esp_log.h>

// Módulos do projeto == /include
#include "constants.h"

/**
 * @struct WiFiParameters
 * @brief WiFi connection settings used to join a station network.
 */
struct WiFiParameters
{
    const char *SSID_STA;      ///< STA SSID to connect to.
    const char *PASSWORD_STA;  ///< STA password.
    int TRY_CONNECTION;        ///< Maximum connection attempts before restart.
};

namespace wifi
{
    /**
     * @brief Connect the device to a WiFi network.
     *
     * @param wifi_data STA connection parameters.
     */
    void connectWiFi(WiFiParameters wifi_data);

    /**
     * @brief Start the device in WiFi Access Point mode.
     *
     * @details
     * The AP mode is used for initial configuration and captive portal access.
     */
    void startAccessPoint();
}
