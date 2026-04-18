#pragma once

// Sensors definitions
constexpr float SEALEVELPRESSURE_HPA = 1013.25;
constexpr int sample_count = 30;
constexpr int sample_dalay = 120000;
constexpr int min_temperature = 18;
constexpr int max_temperature = 24;
constexpr int min_humidity = 40;
constexpr int max_humidity = 60;
constexpr int min_pm_25 = 0;
constexpr int max_pm_25 = 12;

// Wi-Fi Station credentials
constexpr const char *ssid_sta = "Aula";
constexpr const char *password_sta = "20802080";

// Wi-Fi Access Point credentials
constexpr const char *ssid_ap = "Aula";
constexpr const char *password_ap = "20802080";
constexpr int try_connection_seconds = 40;

// MQTT credentials
constexpr const char *MQTT_SERVER = "192.168.137.35";
constexpr int MQTT_PORT = 1883;

// MQTT definitions
constexpr const char *MQTT_TOPIC_PUB = "esp32/test/pub";
constexpr const char *MQTT_TOPIC_SUB = "esp32/test/sub";
constexpr const char *MQTT_CLIENT_ID = "PM_NEXUS_";
constexpr int MQTT_TIME_RECONNECT = 5000;
constexpr int MQTT_MAX_RETRY = 5;