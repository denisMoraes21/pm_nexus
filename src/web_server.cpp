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
            String ssid     = request->getParam("ssid", true)->value();
            String password = request->getParam("password", true)->value();
            String mqtt     = request->getParam("mqtt", true)->value();

#ifdef DEBUG_VALUES
            ESP_LOGI(TAG_WEB, "WIFI - SSID: %s", ssid.c_str());
            ESP_LOGI(TAG_WEB, "WIFI - PASSWORD: %s", password.c_str());
            ESP_LOGI(TAG_WEB, "MQTT: %s", mqtt.c_str());
#endif  

            StaticJsonDocument<256> doc;

            doc["ssid"] = ssid;
            doc["password"] = password;
            doc["mqtt"] = mqtt;

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
