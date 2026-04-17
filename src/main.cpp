#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "DFRobot_AirQualitySensor.h"
#define I2C_ADDRESS    0x19

DFRobot_AirQualitySensor particle(&Wire ,I2C_ADDRESS);

#include "temperature_definition.h"
#include "print_values.h"


void setup() {
  Serial.begin(115200);

  bool status;
  
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
//  status = bme.begin();  
//  if (!status) {
//    Serial.println("Could not find a valid BME280 sensor, check wiring!");
//    while (1);
//  }
  
  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
//  while(!particle.begin())
//  {
//    Serial.println("NO Deivces !");
//    delay(1000);
//  }
  Serial.println("sensor begin success!");
  delay(1000);
  
  uint8_t version = particle.gainVersion();
  Serial.print("version is : ");
  Serial.println(version);
  delay(1000);
}



void loop() {
  printValues(particle);
  delay(delayTime);
}
  
