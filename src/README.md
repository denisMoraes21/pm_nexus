# src Directory

This folder contains the implementation files for the PM Nexus application.
Each `.cpp` file implements a specific module used by the main program.

## Source file descriptions

| File | Purpose |
|------|---------|
| `main.cpp` | Entry point for the application. Initializes hardware and modules, loads configuration from SPIFFS, decides network mode, reads sensors, and publishes data over MQTT. |
| `dns_server.cpp` | Implements DNS server logic used in Access Point mode to support captive portal behavior and configuration access. |
| `ethernet.cpp` | Provides Ethernet connectivity checks and optional wired network support. |
| `led.cpp` | Controls the status LED, including initialization and blinking patterns for feedback. |
| `mqtt.cpp` | Handles MQTT client setup, reconnection logic, and data publishing routines. |
| `sensors.cpp` | Manages sensor initialization and data acquisition for the BME280 and PM2.5 sensors. |
| `sleep.cpp` | Implements low-power deep sleep behavior for energy-efficient operation. |
| `spiffs_utils.cpp` | Manages SPIFFS configuration storage, including reading and writing JSON settings files. |
| `web_server.cpp` | Sets up the web-based configuration interface for first-time device setup and WiFi/MQTT parameter input. |
| `wifi_utils.cpp` | Manages WiFi access point mode, station mode, and connection flow based on saved configuration. |

## Notes

- These source files collaborate with header files in `include/` to keep interfaces and implementations separate.
- `main.cpp` is the central orchestrator for sensor reading, network selection, and MQTT publishing.
- The `src/` directory is the main application layer of the firmware.
