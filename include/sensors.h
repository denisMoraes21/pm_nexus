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

namespace sensors
{
    void initBME250(Adafruit_BME280 &bme);
    void initGRAVITYPM25(DFRobot_AirQualitySensor &particle);
    BME250data getBME250values(Adafruit_BME280 &bme);
    GRAVITYPM25data getGRAVITYPM25values(DFRobot_AirQualitySensor &particle);
    void printBME250Values(BME250data data);
    void printGRAVITYPM25Values(GRAVITYPM25data data);
    float getAvgInt(const std::vector<int> &list_values);
    float getAvgFloat(const std::vector<float> &list_values);
    SensorAVGdata getSensorsAvg(Adafruit_BME280 &bme, DFRobot_AirQualitySensor &particle);
}