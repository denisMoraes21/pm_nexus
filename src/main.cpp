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


// --- [3] CONFIGURAÇÕES DO BROKER MQTT ---
const char* mqtt_server = "192.168.137.35"; // Broker público
const int   mqtt_port   = 1883;                // Porta padrão MQTT
const char* mqtt_topic  = "esp32/teste";    // Tópico de publicação
const char* client_id   = "ESP32Client_Sensor"; // ID único do cliente

// --- [4] INSTÂNCIAS DOS OBJETOS ---
WiFiClient   espClient;           // Cliente Wi-Fi
PubSubClient client(espClient);   // Cliente MQTT usando Wi-Fi

// --- [5] VALORES DOS SENSORES (simulados) ---
// Em produção, substitua pelos valores lidos dos sensores reais
float particula = 2.5;  // Partículas PM2.5 (µm)
int   temp      = 28;   // Temperatura (°C)
int   humid     = 51;   // Umidade relativa (%)

// ============================================================
// FUNÇÃO: conectarWiFi()
// Realiza conexão à rede Wi-Fi e aguarda até ser estabelecida
// ============================================================
void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  WiFi.begin(ssid, password);

  // Aguarda a conexão ser estabelecida (com timeout visual)
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tentativas++;
    if (tentativas > 40) {
      // Após 20 segundos sem conexão, reinicia o ESP
      Serial.println("\n[ERRO] Falha no Wi-Fi. Reiniciando...");
      ESP.restart();
    }
  }

  Serial.println("\n[OK] Wi-Fi conectado!");
  Serial.print("     IP: ");
  Serial.println(WiFi.localIP());
}

// ============================================================
// FUNÇÃO: reconnect()
// Reconexão automática ao broker MQTT em caso de queda
// ============================================================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");

    if (client.connect(client_id)) {
      // Conexão bem-sucedida
      Serial.println("[OK] Conectado ao broker MQTT!");
    } else {
      // Falha na conexão — exibe código de erro e tenta novamente
      Serial.print("[ERRO] Falhou. rc=");
      Serial.print(client.state());
      Serial.println(" | Tentando novamente em 2s...");
      delay(2000);
    }
  }
}

// ============================================================
// FUNÇÃO: publicarDados()
// Monta o payload JSON e publica no tópico MQTT
// ============================================================
void publicarDados() {
  // Cria um documento JSON com capacidade para os campos necessários
  StaticJsonDocument<200> doc;

  // --- Objeto "particle" ---
  JsonObject particle_obj = doc.createNestedObject("particle");
  particle_obj["value"] = particula;
  particle_obj["unit"]  = "um";

  // --- Objeto "temp" ---
  JsonObject temp_obj = doc.createNestedObject("temp");
  temp_obj["value"] = temp;
  temp_obj["unit"]  = "C";

  // --- Objeto "humid" ---
  JsonObject humid_obj = doc.createNestedObject("humid");
  humid_obj["value"] = humid;
  humid_obj["unit"]  = "%";

  // Serializa o JSON para uma String
  String payload;
  serializeJson(doc, payload);

  // Publica no tópico MQTT
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("Mensagem enviada: " + payload);
  } else {
    Serial.println("[ERRO] Falha ao publicar mensagem MQTT.");
  }
}

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

