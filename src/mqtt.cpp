#include "mqtt.h"

WiFiClient wifiClient;
EthernetClient ethClient;
PubSubClient mqtt_client;

const char *TAG_MQTT = "MQTT";

void callback(char *topic, byte *payload, unsigned int length)
{
#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_MQTT, "Message received in topic: %s", topic);
#endif

    char message[length + 1];

    for (unsigned int i = 0; i < length; i++)
    {
        message[i] = (char)payload[i];
    }

    message[length] = '\0';

#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_MQTT, "Message: %s", message);
#endif
}

void mqtt::publishData(SensorAVGdata data, MQTTParameters parameters)
{
    const char *MQTT_TOPIC_PUB = parameters.MQTT_TOPIC_PUB;
    StaticJsonDocument<200> doc;

    JsonObject particle_obj = doc.createNestedObject("particle");
    particle_obj["value"] = data.pm25;
    particle_obj["unit"] = "um";

    JsonObject temp_obj = doc.createNestedObject("temp");
    temp_obj["value"] = data.temp;
    temp_obj["unit"] = "C";

    JsonObject humid_obj = doc.createNestedObject("humid");
    humid_obj["value"] = data.humid;
    humid_obj["unit"] = "%";

    String payload;
    serializeJson(doc, payload);

    if (!mqtt_client.publish(MQTT_TOPIC_PUB, payload.c_str()))
    {

#ifdef DEBUG_VALUES
        ESP_LOGE(TAG_MQTT, "Fail to publish MQTT");
#endif

        ESP.restart();
        return;
    }
    ESP_LOGI(TAG_MQTT, "Mensagem enviada: %s", payload);
}

void mqtt::initMqtt(bool useEthernet, MQTTParameters parameters)
{
    const char *server = parameters.MQTT_SERVER;
    uint16_t port = parameters.MQTT_PORT;
    if (useEthernet)
    {
        mqtt_client.setClient(ethClient);
        ESP_LOGI(TAG_MQTT, "MQTT usando Ethernet");
    }
    else
    {
        mqtt_client.setClient(wifiClient);
        ESP_LOGI(TAG_MQTT, "MQTT usando WiFi");
    }

    mqtt_client.setServer(server, port);
    mqtt_client.setCallback(callback);
}

void mqtt::reconnectMQTT(MQTTParameters parameters)
{
    int MQTT_MAX_RETRY = parameters.MQTT_MAX_RETRY;
    String CLIENT = parameters.MQTT_CLIENT;
    const char *MQTT_TOPIC_SUB = parameters.MQTT_TOPIC_SUB;
    const char *MQTT_TOPIC_PUB = parameters.MQTT_TOPIC_PUB;
    int MQTT_TIME_RECONNECT = parameters.MQTT_TIME_RECONNECT;
    int count = 0;
    while (!mqtt_client.connected() && count < MQTT_MAX_RETRY)
    {

#ifdef DEBUG_VALUES
        ESP_LOGE(TAG_MQTT, "Connecting MQTT...");
#endif

        String clientId = CLIENT;
        clientId += CLIENT;

        if (mqtt_client.connect(clientId.c_str()))
        {

#ifdef DEBUG_VALUES
            ESP_LOGE(TAG_MQTT, "Connected!");
#endif

            mqtt_client.subscribe(MQTT_TOPIC_SUB);
        }
        else
        {

#ifdef DEBUG_VALUES
            ESP_LOGE(TAG_MQTT, "Failed, State: %d", mqtt_client.state());
            ESP_LOGE(TAG_MQTT, "Trying again in %f s", MQTT_TIME_RECONNECT / 1000);
#endif

            delay(MQTT_TIME_RECONNECT);
        }
        count++;
    }

    mqtt_client.loop();
}
