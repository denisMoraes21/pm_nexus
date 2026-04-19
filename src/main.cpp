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
// TODO Add config page costumization

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

    SensorAVGdata data = sensors::getSensorsAvg();
    bool useEthernet = ethernet::checkEthernet();

    if (!useEthernet)
    {
        wifi::connectWiFi();
    }

    led::blink(BLINK_LED_TIME);
    mqtt::initMqtt(useEthernet);
    led::blink(BLINK_LED_TIME);
    mqtt::reconnectMQTT();
    led::blink(BLINK_LED_TIME);
    mqtt::publishData(data);
    led::blink(BLINK_LED_TIME);
}
