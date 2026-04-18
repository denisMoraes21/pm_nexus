// ============================================================
// FUNÇÃO: publicarDados()
// Monta o payload JSON e publica no tópico MQTT
// ============================================================

#pragma once

#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "constants.h"
#include "esp_log.h"
#include "sensors.h"

namespace mqtt
{
  void publishData(SensorAVGdata data);
  void initMqtt();
  void reconnectMQTT();
}