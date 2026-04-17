// --- [3] CONFIGURAÇÕES DO BROKER MQTT ---
const char* mqtt_server = "192.168.137.35"; // Broker público
const int   mqtt_port   = 1883;                // Porta padrão MQTT
const char* mqtt_topic  = "esp32/teste";    // Tópico de publicação
const char* client_id   = "ESP32Client_Sensor"; // ID único do cliente