#pragma once

// Sensors definitions
constexpr int sample_count = 30;
constexpr int sample_dalay = 120000;
constexpr int min_temperature = 18;
constexpr int max_temperature = 24;
constexpr int min_humidity = 40;
constexpr int max_humidity = 60;
constexpr int min_pm_25 = 0;
constexpr int max_pm_25 = 12;

// Wi-Fi credentials
constexpr const char *ssid_sta = "Aula";
constexpr const char *password_sta = "20802080";
constexpr const char *ssid_ap = "Aula";
constexpr const char *password_ap = "20802080";
constexpr int try_connection_seconds = 40;