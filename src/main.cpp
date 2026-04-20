/**
 * @file        main.cpp
 * @brief       Aplicação principal da aplicação
 *
 * @project     PM Nexus
 * @platform    PlatformIO
 * @board       ESP32 Dev Module (esp32dev) - ESP32 WROOM
 * @framework   Arduino
 *
 * @details     Inicializa os módulos do sistema, configura periféricos
 * @architecture
 * sensores:
 * - BME280: sensor de umidade e temperatura.
 * - Gravity air quality sensor PM2.5: medidor de particulas.
 *
 * network:
 * - WiFi: modo access point para cadastro e configuração de dispositivo.
 * - MQTT: Envio de informações coletadas.
 *
 * energia:
 * - Deep Sleep: modo de economia de energia ativado quando sensor estiver ocioso.
 *
 * @authors     Leonardo Souza Gomes, Batalha Amancio, Igor De Oliveira Damasceno, Carlos Daniel Amazonas Da Silva
 * @date        2026-04-17
 * @version     1.1
 * @note        Configurações definidas em platformio.ini
 **/

#include "import_libs.h"

void setup()
{
    Serial.begin(115200);
    sensors::initBME250();
    sensors::initGRAVITYPM25();
    led::initLed();
}

// TODO Add hard reset (button and delete config file)
// TODO Receive mqtt message?
// TODO Limit parameters on config page
// TODO Test connection after user insert parameter

void loop()
{
    led::ledON();
    if (!spi_ffs::settingsFileExists())
    {
        wifi::startAccessPoint();
        dns::initDNS();
        web_server_esp::initWebServer();
        while (1)
            ;
    }

    StaticJsonDocument<1024> doc;
    spi_ffs::readConfigFile(doc);

    WiFiParameters wifi_data{
        doc["ssid"],
        doc["password"],
        doc["try_connection"]};

    MQTTParameters mqtt_data{
        doc["server"],
        doc["port"],
        doc["topic_pub"],
        doc["topic_sub"],
        doc["client"],
        doc["time_reconnect"],
        doc["rety_qty"]};

    SensorParameters sensor_parameters{
        doc["pressure"],
        doc["sample_count"],
        doc["sample_delay"],
        doc["min_temperature"],
        doc["max_temperature"],
        doc["min_humidity"],
        doc["max_humidity"],
        doc["min_pm_25"],
        doc["max_pm_25"]};

    SensorAVGdata sensor_data = sensors::getSensorsAvg(sensor_parameters);
    bool useEthernet = ethernet::checkEthernet();

    if (!useEthernet)
    {
        wifi::connectWiFi(wifi_data);
    }

    led::blink(BLINK_LED_TIME);
    mqtt::initMqtt(useEthernet, mqtt_data);
    led::blink(BLINK_LED_TIME);
    mqtt::reconnectMQTT(mqtt_data);
    led::blink(BLINK_LED_TIME);
    mqtt::publishData(sensor_data, mqtt_data);
    led::blink(BLINK_LED_TIME);
}
