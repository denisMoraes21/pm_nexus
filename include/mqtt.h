// ============================================================
// FUNÇÃO: publicarDados()
// Monta o payload JSON e publica no tópico MQTT
// ============================================================

#pragma once

#include <Ethernet.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "constants.h"
#include "esp_log.h"
#include "sensors.h"

struct MQTTParameters
{
    const char *MQTT_SERVER;
    int MQTT_PORT;
    const char *MQTT_TOPIC_PUB;
    const char *MQTT_TOPIC_SUB;
    const char *MQTT_CLIENT;
    int MQTT_TIME_RECONNECT;
    int MQTT_MAX_RETRY;
};

namespace mqtt
{
    void publishData(SensorAVGdata data, MQTTParameters parameters);
    void initMqtt(bool useEthernet, MQTTParameters parameters);
    void reconnectMQTT(MQTTParameters parameters);
}