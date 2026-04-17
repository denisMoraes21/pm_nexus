// ============================================================
// PROJETO: Envio de Dados de Sensores via MQTT com ESP32
// PLATAFORMA: Arduino IDE 2.3.8 | ESP32
// BIBLIOTECAS: WiFi.h, PubSubClient.h, ArduinoJson.h
// AUTOR: Gerado para fins educacionais
// ============================================================

// --- [1] INCLUSÃO DE BIBLIOTECAS ---
#include <WiFi.h>          // Conexão Wi-Fi do ESP32
#include <PubSubClient.h>  // Comunicação MQTT (broker pub/sub)
#include <ArduinoJson.h>   // Criação de payload JSON
#include "wifi_config.h"
#include "mqtt.h"
#include "WiFi_Client.h"
#include "WiFi_reconnect.h"
#include "Public_dados.h"

// ============================================================
// SETUP: Executado uma vez na inicialização
// ============================================================
void setup() {
  Serial.begin(115200); // Inicia comunicação serial (monitor)
  Serial.println("\n=== Sistema de Sensores MQTT ===");

  conectarWiFi();                        // Conecta ao Wi-Fi
  client.setServer(mqtt_server, mqtt_port); // Configura o broker MQTT
}

// ============================================================
// LOOP: Executado continuamente
// ============================================================
void loop() {
  // Verifica conexão Wi-Fi — reconecta se necessário
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[AVISO] Wi-Fi perdido. Reconectando...");
    // WiFi.disconnect();     // encerra conexão atual antes de reconectar
    conectarWiFi();
  }

  // Verifica conexão MQTT — reconecta se necessário
  if (!client.connected()) {
    reconnect();
  }

  // Mantém a conexão MQTT ativa (processamento interno da lib)
  client.loop();

  // Publica os dados dos sensores
  publicarDados();

  // Aguarda 5 segundos antes do próximo envio
  delay(5000);
}

