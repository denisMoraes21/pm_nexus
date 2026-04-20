#pragma once

#include <SPI.h>
#include <Ethernet.h>
#include "esp_log.h"

namespace ethernet
{
    /**
     * @brief Generate a unique MAC address for the Ethernet interface.
     *
     * @param mac Output buffer to receive the generated MAC address.
     *
     * @details
     * Uses the ESP32 chip identifier and a random byte to build a locally
     * administered MAC address compatible with the Ethernet module.
     */
    void generateMAC(byte mac[6]);

    /**
     * @brief Initialize and verify Ethernet connectivity.
     *
     * @return true if Ethernet is initialized and has a valid link and IP address.
     * @return false if initialization fails, the link is down, or no valid IP is assigned.
     */
    bool checkEthernet();
}