#include "dns_server.h"

const byte DNS_PORT = 53;
DNSServer dns_server;

void dns::initDNS()
{
    dns_server.start(DNS_PORT, "*", WiFi.softAPIP());
}

void dns::loopDNS()
{
    dns_server.processNextRequest();
}