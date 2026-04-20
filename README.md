# PM Nexus

## Overview

PM Nexus is an IoT project designed for particle counting in clean rooms. It utilizes an ESP32 microcontroller to collect environmental data including temperature, humidity, and PM2.5 particle levels. The system features WiFi connectivity for configuration and MQTT for data transmission, with deep sleep capabilities for energy efficiency.

## Features

- **Sensors Integration**:
  - BME280: Measures temperature and humidity.
  - Gravity Air Quality Sensor PM2.5: Measures particulate matter (PM2.5).

- **Networking**:
  - WiFi Access Point mode for initial device configuration.
  - MQTT client for publishing sensor data to a broker.

- **Energy Management**:
  - Deep Sleep mode to conserve power when idle.

- **Web Interface**:
  - Built-in web server for configuration via a browser.

- **Data Storage**:
  - SPIFFS for storing configuration settings.

## Hardware Requirements

- ESP32 Dev Module (ESP32 WROOM)
- BME280 sensor
- Gravity Air Quality Sensor PM2.5
- Ethernet module (optional, for wired connectivity)
- LED for status indication

## Software Requirements

- [PlatformIO](https://platformio.org/) IDE
- Arduino Framework
- Required Libraries (included in `lib/`):
  - Adafruit_BME280_Library
  - Adafruit_BusIO
  - Adafruit_IO_Arduino
  - Adafruit_Sensor
  - DFRobot_AirQualitySensor

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/pm_nexus.git
   cd pm_nexus
   ```

2. Open the project in PlatformIO.

3. Install dependencies (PlatformIO will handle this automatically).

4. Build the project:

   ```bash
   platformio run
   ```

5. Upload to ESP32:

   ```bash
   platformio run --target upload --environment dev
   ```

## Configuration

1. On first boot, the ESP32 enters Access Point mode.
2. Connect to the WiFi network created by the device.
3. Open a browser and navigate to the device's IP (usually 192.168.4.1).
4. Configure WiFi credentials, MQTT settings, and sensor parameters via the web interface.

Configuration parameters include:

- WiFi SSID and password
- MQTT server, port, topics, client ID
- Sensor thresholds (temperature, humidity, PM2.5 ranges)
- Sampling settings (count, delay)

## Usage

1. Power on the device.
2. If not configured, enter AP mode for setup.
3. Once configured, the device will:
   - Collect sensor data at specified intervals.
   - Connect to WiFi or Ethernet.
   - Publish data via MQTT.
   - Enter deep sleep to save power.

Monitor the serial output for debugging information.

## Web Application

The project includes a web application with a backend API and a frontend dashboard for monitoring sensor data.

### Backend

The backend is built with Python using Flask and provides REST API endpoints for retrieving sensor data and managing configurations. It also handles MQTT communication and database storage.

#### Prerequisites

- Python 3.8+
- pip
- SQLite (for database)
- MQTT Broker (e.g., Mosquitto)

#### Installation

1. Navigate to the backend directory:

   ```bash
   cd web/backend
   ```

2. Install dependencies:

   ```bash
   pip install flask flask-cors paho-mqtt
   ```

3. Run the application:

   ```bash
   python app.py
   ```

The backend will start on `http://localhost:5000` and connect to the MQTT broker.

### Frontend

The frontend is a React application that provides a user interface for viewing sensor data and configuring the system.

#### Prerequisites

- Node.js 14+
- npm

#### Installation

1. Navigate to the frontend directory:

   ```bash
   cd web/frontend
   ```

2. Install dependencies:

   ```bash
   npm install
   ```

3. Start the development server:

   ```bash
   npm start
   ```

The frontend will be available at `http://localhost:3000`.

## Architecture

The project is modularized into several components:

- **Sensors**: Handles BME280 and PM2.5 sensor initialization and data reading.
- **WiFi**: Manages WiFi connections and Access Point mode.
- **MQTT**: Handles MQTT client operations.
- **Web Server**: Provides configuration interface.
- **SPIFFS Utils**: Manages configuration file storage.
- **Ethernet**: Optional wired connectivity.
- **LED**: Status indication.
- **Sleep**: Deep sleep management.
- **DNS Server**: For AP mode.

## Project Structure

```
pm_nexus/
├── platformio.ini          # PlatformIO configuration
├── src/                    # Source files
│   ├── main.cpp            # Main application
│   ├── sensors.cpp         # Sensor handling
│   ├── wifi_utils.cpp      # WiFi utilities
│   ├── mqtt.cpp            # MQTT client
│   ├── web_server.cpp     # Web server
│   └── ...
├── include/                # Header files
│   ├── sensors.h
│   ├── wifi_utils.h
│   └── ...
├── lib/                    # Libraries
│   ├── Adafruit_BME280_Library-master/
│   ├── Adafruit_BusIO-master/
│   └── ...
├── data/                   # Web interface files
│   ├── index.html
│   ├── style.css
│   └── ...
├── web/                    # Web application
│   ├── backend/            # Flask API server
│   │   ├── app.py          # Main Flask application
│   │   ├── database.py     # Database utilities
│   │   ├── mqtt.py         # MQTT client
│   │   └── logger.py       # Logging utilities
│   └── frontend/           # React dashboard
│       ├── package.json    # Node.js dependencies
│       ├── public/         # Static files
│       └── src/            # React source code
└── test/                   # Test files
```

## Contributing

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authors

- Leonardo Souza Gomes
- Batalha Amancio
- Igor De Oliveira Damasceno
- Carlos Daniel Amazonas Da Silva

## Version

1.1 - April 17, 2026

## Notes

- Configurations are defined in `platformio.ini`.
- TODO: Add hard reset functionality.
- TODO: Implement MQTT message reception.
- TODO: Add parameter limits on config page.
- TODO: Test connection after user inputs parameters.
