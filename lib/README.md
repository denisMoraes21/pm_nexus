
# lib Directory

This folder contains third-party and project-specific libraries used by PM Nexus.
PlatformIO compiles each library into the final firmware and links it automatically.

## Included libraries

| Library folder | Purpose |
|----------------|---------|
| `Adafruit_BME280_Library-master` | Driver library for the BME280 environmental sensor (temperature, humidity, pressure). |
| `Adafruit_BusIO-master` | Utility layer for I2C/SPI communication used by Adafruit sensor libraries. |
| `Adafruit_IO_Arduino-master` | MQTT and Adafruit IO communication client for remote publishing. |
| `Adafruit_Sensor-master` | Sensor abstraction layer used by Adafruit sensor drivers. |
| `DFRobot_AirQualitySensor-master` | Driver library for the Gravity PM2.5 air quality sensor. |

## Purpose in this project

- `Adafruit_BME280_Library-master` reads environmental data from the BME280 sensor.
- `DFRobot_AirQualitySensor-master` reads PM2.5 particle concentration data.
- `Adafruit_BusIO-master` provides common I2C/SPI helpers and device communication support.
- `Adafruit_Sensor-master` provides the shared sensor interface and data structures.
- `Adafruit_IO_Arduino-master` is included for MQTT/adaptor compatibility and cloud transport.

## Notes

- These libraries are vendor-supplied and are kept in separate folders for compatibility.
- PlatformIO Library Dependency Finder (LDF) discovers required headers and sources automatically.
- Keep the folder structure consistent with PlatformIO conventions when adding or updating libraries.

## Recommended structure

Each library should live in its own folder under `lib/`, with code and metadata grouped together.
PlatformIO builds each library once and links it with the application from `src/`.

More information:
- https://docs.platformio.org/page/librarymanager/ldf.html
