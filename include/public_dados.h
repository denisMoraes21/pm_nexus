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