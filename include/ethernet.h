#pragma once

#include <SPI.h>
#include <Ethernet.h>
#include "esp_log.h"

namespace ethernet
{
    void generateMAC(byte mac[6]);
    bool checkEthernet();
}