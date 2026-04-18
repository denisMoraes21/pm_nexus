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

// Bibliotecas externas == /lib
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <DFRobot_AirQualitySensor.h>
#include <PubSubClient.h>
#include <Wire.h>

// Módulos do projeto == /include
#include "deep_sleep.h"
#include "led_function.h"
#include "led_state.h"
#include "mqtt.h"
#include "pin_definition.h"
#include "sensors.h"
#include "temperature_definition.h"
#include "wifi_utils.h"
#include "public_dados.h"
#include "WiFi_reconnect.h"

#include "DFRobot_AirQualitySensor.h"
#include <Adafruit_BME280.h>

// Instâncias de sensores
DFRobot_AirQualitySensor particle(&Wire);
Adafruit_BME280 bme;

// Estado do LED
bool ledLigado = false;

void setup()
{
  Serial.begin(115200);
  sensors::initBME250(bme);
  sensors::initGRAVITYPM25(particle);

  bool status;

  pinMode(pinoLED, OUTPUT);
  // deep_sleep(5);
}

void loop()
{
  SensorAVGdata data = sensors::getSensorsAvg(bme, particle);

  delay(5000);

  // conectarWiFi();
  // client.setServer(mqtt_server, mqtt_port);

  // // Verifica conexão Wi-Fi — reconecta se necessário
  // if (WiFi.status() != WL_CONNECTED)
  // {
  //   Serial.println("[AVISO] Wi-Fi perdido. Reconectando...");
  //   conectarWiFi();
  // }

  // // Verifica conexão MQTT — reconecta se necessário
  // if (!client.connected())
  // {
  //   reconnect();
  // }

  // // Mantém a conexão MQTT ativa (processamento interno da lib)
  // client.loop();

  // // Publica os dados dos sensores
  // publicarDados();

  // // Aguarda 5 segundos antes do próximo envio
  // delay(5000);

  // // 🔴 DESLIGADO
  // desligar(ledLigado);
  // delay(2000);

  // // 🟢 LIGADO - Baixa intensidade
  // ligar(ledLigado);
  // pwmManual(200, 800, 5000, ledLigado);

  // // 🟡 Média intensidade
  // pwmManual(500, 500, 5000, ledLigado);

  // // 🔵 Alta intensidade
  // pwmManual(800, 200, 5000, ledLigado);

  // // 🔴 DESLIGA novamente
  // desligar(ledLigado);
  // delay(2000);

  // // ⚡ BLINK (liga/desliga)
  // for (int i = 0; i < 5; i++)
  // {
  //   ligar(ledLigado);
  //   digitalWrite(pinoLED, HIGH);
  //   delay(1000);

  //   desligar(ledLigado);
  //   delay(1000);
  // }
}
