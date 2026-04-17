// --- [4] INSTÂNCIAS DOS OBJETOS ---
#include "WiFiClient.h"
#include <PubSubClient.h> 
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



