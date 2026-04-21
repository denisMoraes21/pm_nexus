#include "web_server.h"

AsyncWebServer server(80);
const char *TAG_WEB = "WEB_SERVER";

void web_server_esp::initWebServer()
{

    server.on(
        "/config",
        HTTP_POST, [](AsyncWebServerRequest *request)
        {
#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "Route: 'config' ");
#endif      
            // Wi-Fi
            String ssid         = request->getParam("ssid", true)->value();
            String password     = request->getParam("password", true)->value();
            int try_connection  = request->getParam("try_connection", true)->value().toInt();
            
            // MQTT
            String server       = request->getParam("server", true)->value();
            int port            = request->getParam("port", true)->value().toInt();
            String topic_pub    = request->getParam("topic_pub", true)->value();
            String topic_sub    = request->getParam("topic_sub", true)->value();
            String client       = request->getParam("client", true)->value();
            int time_reconnect  = request->getParam("time_reconnect", true)->value().toInt();
            int max_retry       = request->getParam("max_retry", true)->value().toInt();

            // Sensor
            float pressure      = request->getParam("pressure", true)->value().toFloat();
            int sample_count    = request->getParam("sample_count", true)->value().toInt();
            int sample_delay    = request->getParam("sample_delay", true)->value().toInt();
            int min_temperature = request->getParam("min_temperature", true)->value().toInt();
            int max_temperature = request->getParam("max_temperature", true)->value().toInt();
            int min_humidity    = request->getParam("min_humidity", true)->value().toInt();
            int max_humidity    = request->getParam("max_humidity", true)->value().toInt();
            int min_pm_25       = request->getParam("min_pm_25", true)->value().toInt();
            int max_pm_25       = request->getParam("max_pm_25", true)->value().toInt();

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "WIFI - ssid: %s--", ssid.c_str());
            ESP_LOGI(TAG_WEB, "WIFI - password: %s", password.c_str());

            ESP_LOGI(TAG_WEB, "MQTT - server: %s", server.c_str());
            ESP_LOGI(TAG_WEB, "MQTT - port: %d", port);
            ESP_LOGI(TAG_WEB, "MQTT - topic pub: %s", topic_pub.c_str());
            ESP_LOGI(TAG_WEB, "MQTT - topic sub: %s", topic_sub.c_str());
            ESP_LOGI(TAG_WEB, "MQTT - client: %s", topic_sub.c_str());
            ESP_LOGI(TAG_WEB, "MQTT - time reconnect: %d", time_reconnect);
            ESP_LOGI(TAG_WEB, "MQTT - max retry: %d", max_retry);

            ESP_LOGI(TAG_WEB, "MQTT - pressure: %f", pressure);
            ESP_LOGI(TAG_WEB, "MQTT - sample count: %d", sample_count);
            ESP_LOGI(TAG_WEB, "MQTT - sample delay: %d", sample_delay);
            ESP_LOGI(TAG_WEB, "MQTT - min temperature: %d", min_temperature);
            ESP_LOGI(TAG_WEB, "MQTT - max temperature: %d", max_temperature);
            ESP_LOGI(TAG_WEB, "MQTT - min PM 2.5: %d", min_pm_25);
            ESP_LOGI(TAG_WEB, "MQTT - max PM 2.5: %d", max_pm_25);
#endif  

            StaticJsonDocument<1024> doc;

            doc["ssid"] = ssid;
            doc["password"] = password;
            doc["try_connection"] = try_connection;
            
            doc["server"] = server;
            doc["port"] = port;
            doc["topic_pub"] = topic_pub;
            doc["topic_sub"] = topic_sub;
            doc["client"] = client;
            doc["time_reconnect"] = time_reconnect;
            doc["rety_qty"] = max_retry;

            doc["pressure"] = pressure;
            doc["sample_count"] = sample_count;
            doc["sample_delay"] = sample_delay;
            doc["min_temperature"] = min_temperature;
            doc["max_temperature"] = max_temperature;
            doc["min_humidity"] = min_humidity;
            doc["max_humidity"] = max_humidity;
            doc["min_pm_25"] = min_pm_25;
            doc["max_pm_25"] = max_pm_25;

            String json;
            serializeJson(doc, json);

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "JSON: %s", json.c_str());
#endif

            spi_ffs::createFile(json.c_str());

            request->send(200, "text/plain", "Salvo! Reiniciando...");

            delay(1000);
            ESP.restart(); });

    server.onNotFound([](AsyncWebServerRequest *request)
                      {

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "Route: Not Found !! Redirect to '/config' ");
#endif

                        request->redirect("/"); });

    server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request)
              {

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "Route: /generate_204, Redirect to '/config' ");
#endif

                request->send(200, "text/plain", "OK"); });

    server.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest *request)
              {

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "Route: /hotspot-detect.html, Redirect to '/config' ");
#endif

                request->redirect("/"); });

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.begin();
}
