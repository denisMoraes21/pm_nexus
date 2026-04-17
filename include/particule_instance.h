#include "DFRobot_AirQualitySensor.h"

#define I2C_ADDRESS    0x19

DFRobot_AirQualitySensor particle(&Wire ,I2C_ADDRESS);