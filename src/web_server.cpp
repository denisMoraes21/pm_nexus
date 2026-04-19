#include "web_server.h"

AsyncWebServer server(80);
const char *TAG_WEB = "WEB_SERVER";

void web_server_esp::initWebServer()
{
    server.on(
        "/",
        HTTP_GET,
        [](AsyncWebServerRequest *request)
        {
            request->send(200, "text/plain", "SERVER OK!");
        });

    server.on(
        "/config",
        HTTP_POST, [](AsyncWebServerRequest *request)
        {
            String ssid     = request->getParam("ssid", true)->value();
            String password = request->getParam("password", true)->value();
            String mqtt     = request->getParam("mqtt", true)->value();

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "SSID: %s", ssid);
            ESP_LOGI(TAG_WEB, "PASSWORD: %s", password);
            ESP_LOGI(TAG_WEB, "MQTT: %s", mqtt);
#endif  

            StaticJsonDocument<256> doc;

            doc["ssid"] = ssid;
            doc["password"] = password;
            doc["mqtt"] = mqtt;

            String json;
            serializeJson(doc, json);

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "JSON: %s", json);
#endif

            spi_ffs::createFile(json.c_str());

            request->send(200, "text/plain", "Salvo! Reiniciando...");

            delay(1000);
            ESP.restart(); });

    server.begin();
}
