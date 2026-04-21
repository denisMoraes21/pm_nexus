#pragma once

#include <DNSServer.h>
#include <WiFi.h>
#include <SPIFFS.h>

namespace dns
{
    /**
     * @brief Initialize the DNS server for Access Point mode.
     *
     * @details
     * Starts the DNS server on port 53 and responds to all hostnames with
     * the ESP32 SoftAP IP address. This enables captive portal behavior so
     * users can access the configuration web interface without knowing the
     * exact device IP.
     */
    void initDNS();

    /**
     * @brief Process incoming DNS requests.
     *
     * @details
     * Call this regularly from the main loop while the device is running in
     * Access Point mode. It processes pending DNS queries and keeps the captive
     * portal available for connected clients.
     */
    void loopDNS();
}