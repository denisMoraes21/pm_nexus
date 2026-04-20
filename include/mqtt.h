// ============================================================
// MQTT module interface
// ============================================================

#pragma once

#include <Ethernet.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "constants.h"
#include "esp_log.h"
#include "sensors.h"

/**
 * @struct MQTTParameters
 * @brief MQTT connection and topic configuration parameters.
 */
struct MQTTParameters
{
    const char *MQTT_SERVER;   ///< MQTT broker hostname or IP address.
    int MQTT_PORT;            ///< MQTT broker port.
    const char *MQTT_TOPIC_PUB;///< Publish topic for sensor data.
    const char *MQTT_TOPIC_SUB;///< Subscription topic for incoming messages.
    const char *MQTT_CLIENT;  ///< MQTT client identifier.
    int MQTT_TIME_RECONNECT;  ///< Reconnection delay in milliseconds.
    int MQTT_MAX_RETRY;       ///< Maximum number of MQTT connection attempts.
};

namespace mqtt
{
    /**
     * @brief Publish sensor data to the configured MQTT topic.
     *
     * @param data Aggregated sensor measurements.
     * @param parameters MQTT connection and topic configuration.
     */
    void publishData(SensorAVGdata data, MQTTParameters parameters);

    /**
     * @brief Initialize MQTT client settings.
     *
     * @param useEthernet If true, use Ethernet client; otherwise use WiFi client.
     * @param parameters MQTT connection and topic configuration.
     */
    void initMqtt(bool useEthernet, MQTTParameters parameters);

    /**
     * @brief Reconnect to the MQTT broker if not already connected.
     *
     * @param parameters MQTT connection and retry settings.
     */
    void reconnectMQTT(MQTTParameters parameters);
}