#pragma once

#include <Arduino.h>
#include "DFRobot_AirQualitySensor.h"
#include <Adafruit_BME280.h>
#include <vector>
#include "esp_log.h"
#include "constants.h"
#include "sleep.h"

struct BME250data
{
    float temp;
    float press;
    float alt;
    float humid;
};

struct GRAVITYPM25data
{
    int pm1;
    int pm25;
    int pm10;
};

struct SensorAVGdata
{
    float temp;
    float press;
    float alt;
    float humid;
    float pm1;
    float pm25;
    float pm10;
};

struct SensorParameters
{
    float SEALEVELPRESSURE_HPA;
    int sample_count;
    int sample_delay;
    int min_temperature;
    int max_temperature;
    int min_humidity;
    int max_humidity;
    int min_pm_25;
    int max_pm_25;
};

namespace sensors
{
    void initBME250();
    void initGRAVITYPM25();
    BME250data getBME250values(int min_temperature,
                               int max_temperature,
                               int min_humidity,
                               int max_humidity);
    GRAVITYPM25data getGRAVITYPM25values(int min_pm_25, int max_pm_25);
    void printBME250Values(BME250data bme_250_data);
    void printGRAVITYPM25Values(GRAVITYPM25data particule_data);
    float getAvgInt(const std::vector<int> &list_values);
    float getAvgFloat(const std::vector<float> &list_values);
    SensorAVGdata getSensorsAvg(SensorParameters parameters);
}