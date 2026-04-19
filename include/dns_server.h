#pragma once

#include <DNSServer.h>
#include <WiFi.h>
#include <SPIFFS.h>

namespace dns
{
    void initDNS();
    void loopDNS();
}