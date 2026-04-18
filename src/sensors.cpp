#include "sensors.h"

void sensors::initBME250(Adafruit_BME280 &bme)
{
#ifndef ENABLE_SENSORS
    status = bme.begin();
    if (!status)
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1)
            ;
    }
#endif
}

void sensors::initGRAVITYPM25(DFRobot_AirQualitySensor &particle)
{
#ifndef ENABLE_SENSORS
    while (!particle.begin())
    {
        Serial.println("NO Deivces !");
        delay(1000);
    }
    Serial.println("sensor begin success!");
    delay(1000);
#endif
}

BME250data sensors::getBME250values(Adafruit_BME280 &bme)
{

    BME250data data;

#ifdef ENABLE_SENSORS
    data.temp = random(min_temperature, max_temperature);
    data.press = random(800, 1200);
    data.alt = random(2000, 3000);
    data.humid = random(min_humidity, max_humidity);
#else
    data.temp = bme.readTemperature();
    data.press = bme.readPressure() / 100.0F;
    data.alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
    data.humid = bme.readHumidity();
#endif

    return data;
}

GRAVITYPM25data sensors::getGRAVITYPM25values(DFRobot_AirQualitySensor &particle)
{

    GRAVITYPM25data data;

#ifdef ENABLE_SENSORS
    data.pm25 = random(min_pm_25, max_pm_25);
    data.pm1 = random(0, 12);
    data.pm10 = random(0, 12);
#else
    data.pm25 = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_ATMOSPHERE);
    data.pm1 = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_ATMOSPHERE);
    data.pm10 = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_ATMOSPHERE);
#endif

    return data;
}

void sensors::printBME250Values(BME250data data)
{
#ifdef DEBUG_VALUES
    const char *TAG = "BOSCH";
    ESP_LOGI(TAG, "Temperature = %.2f °C", data.temp);
    ESP_LOGI(TAG, "Pressure = %.2f hPa", data.press);
    ESP_LOGI(TAG, "Altitude = %.2f m", data.alt);
    ESP_LOGI(TAG, "Humidity = %.2f %%", data.humid);
#endif
}

void sensors::printGRAVITYPM25Values(GRAVITYPM25data data)
{
#ifdef DEBUG_VALUES
    const char *TAG = "DFROBOT";
    ESP_LOGI(TAG, "PM1.0 = %.2f ug/m3", data.pm1);
    ESP_LOGI(TAG, "PM2.5 = %.2f ug/m3", data.pm25);
    ESP_LOGI(TAG, "PM10 = %.2f ug/m3", data.pm10);
#endif
}

float sensors::getAvgInt(const std::vector<int> &list_values)
{
    int soma = 0;

    // Avoid division per zero
    if (list_values.empty())
        return 0.0f;

    for (int valor : list_values)
    {
        soma += valor;
    }
    const float avg = soma / list_values.size();
    return avg;
}

float sensors::getAvgFloat(const std::vector<float> &list_values)
{
    float soma = 0;

    // avoid division per zero
    if (list_values.empty())
        return 0.0f;

    for (float valor : list_values)
    {
        soma += valor;
    }
    const float avg = soma / list_values.size();
    return avg;
}

SensorAVGdata sensors::getSensorsAvg(Adafruit_BME280 &bme, DFRobot_AirQualitySensor &particle)
{
    std::vector<float> temp_values;
    std::vector<float> humid_values;
    std::vector<int> particle_values_1;
    std::vector<int> particle_values_25;
    std::vector<int> particle_values_10;

    for (int i = 0; i < sample_count; i++)
    {
        BME250data bme_250_data = sensors::getBME250values(bme);
        sensors::printBME250Values(bme_250_data);

        const float temperature = bme_250_data.temp;
        const float humidity = bme_250_data.humid;

        // Temperatura e umidade está dentro da spec?
        if (
            (temperature > min_temperature && temperature < max_temperature) &&
            (humidity > min_humidity && humidity < max_humidity))
        {
            GRAVITYPM25data particule_data = sensors::getGRAVITYPM25values(particle);
            sensors::printGRAVITYPM25Values(particule_data);

            const int pm_1 = particule_data.pm1;
            const int pm_25 = particule_data.pm25;
            const int pm_10 = particule_data.pm10;

            // Quantidade de particulas está dentro da spec?
            if (pm_25 > min_pm_25 && pm_25 < max_pm_25)
            {

                temp_values.push_back(temperature);
                humid_values.push_back(humidity);
                particle_values_1.push_back(pm_1);
                particle_values_25.push_back(pm_25);
                particle_values_10.push_back(pm_10);

#ifndef SLEEPING_MODE
                sleep_mode::deep_sleep(sample_dalay);
#else
                delay(sample_dalay);
#endif
            }
        }
    }

    float temp = sensors::getAvgFloat(temp_values);
    float humid = sensors::getAvgFloat(humid_values);
    float particle_1 = sensors::getAvgInt(particle_values_1);
    float particle_25 = sensors::getAvgInt(particle_values_25);
    float particle_10 = sensors::getAvgInt(particle_values_10);

    SensorAVGdata data = {
        temp,
        0.0f,
        0.0f,
        humid,
        particle_1,
        particle_25,
        particle_10};
    return data;
}
