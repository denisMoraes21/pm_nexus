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
    delay(1000)
#endif
}

BME250data sensors::getBME250values(Adafruit_BME280 &bme)
{

    BME250data data;

#ifdef ENABLE_SENSORS
    data.temp = random(25, 50);
    data.press = random(800, 1200);
    data.alt = random(2000, 3000);
    data.humid = random(40, 60);
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
    data.pm25 = random(4, 10);
    data.pm1 = random(4, 10);
    data.pm10 = random(4, 10);
#else
    data.pm25 = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_ATMOSPHERE);
    data.pm1 = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_ATMOSPHERE);
    data.pm10 = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_ATMOSPHERE);
#endif

    return data;
}

void sensors::printBME250Values(BME250data data)
{
    Serial.printf("Temperature = %.2f *C\n", data.temp);
    Serial.printf("Pressure = %.2f hPa\n", data.press);
    Serial.printf("Altitude = %.2f m", data.alt);
    Serial.printf("Humidity = %.2f %\n", data.humid);
}

void sensors::printGRAVITYPM25Values(GRAVITYPM25data data)
{
    Serial.printf("PM1.0 = %.2f ug/m3", data.pm1);
    Serial.printf("PM2.5 = %.2f ug/m3", data.pm25);
    Serial.printf("PM10 = %.2f ug/m3", data.pm10);
}

float getAvg(const std::vector<int> list_values)
{
}