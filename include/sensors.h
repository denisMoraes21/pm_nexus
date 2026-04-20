#pragma once

#include <Arduino.h>
#include "DFRobot_AirQualitySensor.h"
#include <Adafruit_BME280.h>
#include <vector>
#include "esp_log.h"
#include "constants.h"
#include "sleep.h"

/**
 * @struct BME250data
 * @brief Encapsulates BME280 sensor measurements.
 */
struct BME250data
{
    float temp;   ///< Temperature in degrees Celsius.
    float press;  ///< Atmospheric pressure in hPa.
    float alt;    ///< Calculated altitude in meters.
    float humid;  ///< Relative humidity in percent.
};

/**
 * @struct GRAVITYPM25data
 * @brief Encapsulates PM2.5 sensor concentration values.
 */
struct GRAVITYPM25data
{
    int pm1;   ///< PM1.0 concentration.
    int pm25;  ///< PM2.5 concentration.
    int pm10;  ///< PM10 concentration.
};

/**
 * @struct SensorAVGdata
 * @brief Aggregated average values from all sensors.
 */
struct SensorAVGdata
{
    float temp;   ///< Average temperature.
    float press;  ///< Average pressure.
    float alt;    ///< Average altitude.
    float humid;  ///< Average humidity.
    float pm1;    ///< Average PM1.0.
    float pm25;   ///< Average PM2.5.
    float pm10;   ///< Average PM10.
};

/**
 * @struct SensorParameters
 * @brief Configuration values used during sensor sampling.
 */
struct SensorParameters
{
    float SEALEVELPRESSURE_HPA; ///< Sea level pressure for altitude calculation.
    int sample_count;          ///< Number of samples to collect.
    int sample_delay;          ///< Delay between samples in milliseconds.
    int min_temperature;       ///< Minimum acceptable temperature.
    int max_temperature;       ///< Maximum acceptable temperature.
    int min_humidity;          ///< Minimum acceptable humidity.
    int max_humidity;          ///< Maximum acceptable humidity.
    int min_pm_25;             ///< Minimum acceptable PM2.5 concentration.
    int max_pm_25;             ///< Maximum acceptable PM2.5 concentration.
};

namespace sensors
{
    /**
     * @brief Initialize the BME280 environmental sensor.
     */
    void initBME250();

    /**
     * @brief Initialize the Gravity PM2.5 air quality sensor.
     */
    void initGRAVITYPM25();

    /**
     * @brief Read measurement values from the BME280 sensor.
     *
     * @param min_temperature Minimum temperature used when sampling.
     * @param max_temperature Maximum temperature used when sampling.
     * @param min_humidity Minimum humidity used when sampling.
     * @param max_humidity Maximum humidity used when sampling.
     * @return BME250data Sensor measurement values.
     */
    BME250data getBME250values(int min_temperature,
                               int max_temperature,
                               int min_humidity,
                               int max_humidity);

    /**
     * @brief Read PM concentration values from the Gravity PM2.5 sensor.
     *
     * @param min_pm_25 Minimum PM2.5 value used when sampling.
     * @param max_pm_25 Maximum PM2.5 value used when sampling.
     * @return GRAVITYPM25data Particle concentration values.
     */
    GRAVITYPM25data getGRAVITYPM25values(int min_pm_25, int max_pm_25);

    /**
     * @brief Log BME280 sensor values when debugging is enabled.
     *
     * @param bme_250_data The BME280 measurement values to print.
     */
    void printBME250Values(BME250data bme_250_data);

    /**
     * @brief Log Gravity PM2.5 sensor values when debugging is enabled.
     *
     * @param particule_data The PM sensor measurement values to print.
     */
    void printGRAVITYPM25Values(GRAVITYPM25data particule_data);

    /**
     * @brief Calculate the average of a list of integer values.
     *
     * @param list_values Values to average.
     * @return float The calculated average, or 0.0 if the list is empty.
     */
    float getAvgInt(const std::vector<int> &list_values);

    /**
     * @brief Calculate the average of a list of float values.
     *
     * @param list_values Values to average.
     * @return float The calculated average, or 0.0 if the list is empty.
     */
    float getAvgFloat(const std::vector<float> &list_values);

    /**
     * @brief Collect and average sensor readings using configured parameters.
     *
     * @param parameters Sensor sampling and threshold configuration.
     * @return SensorAVGdata Aggregated averaged results.
     */
    SensorAVGdata getSensorsAvg(SensorParameters parameters);
}