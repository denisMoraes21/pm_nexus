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