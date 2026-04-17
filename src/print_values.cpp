#include <Arduino.h>
#include "DFRobot_AirQualitySensor.h"



void printValues(DFRobot_AirQualitySensor particle) {
  Serial.print("Temperature = ");
  int temp = random(25 , 50);
  Serial.print(temp);
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  int pres = random(800 , 1200);
  Serial.print(pres);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude = ");
  int alt = random(2000 , 3000);
  Serial.print(alt);
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  int humid = random(40 , 60);
  Serial.print(humid);
  Serial.println(" %");
  
  Serial.println();
  
  uint16_t PM2_5 = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_ATMOSPHERE );
  uint16_t PM1_0 = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_ATMOSPHERE );
  uint16_t PM10 = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_ATMOSPHERE);
  Serial.print("PM2.5 concentration:");
  PM2_5 = random(4 , 10);
  Serial.print(PM2_5);
  Serial.println(" ug/m3");
  Serial.print("PM1.0 concentration:");
  PM1_0 = random(4 , 10);
  Serial.print(PM1_0);
  Serial.println(" ug/m3");
  Serial.print("PM10 concentration:");
  PM10 = random(4 , 10);
  Serial.print(PM10);
  Serial.println(" ug/m3");
  Serial.println();
  delay(1000);
}