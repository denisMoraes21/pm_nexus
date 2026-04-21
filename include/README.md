
# Include Directory

This folder contains the project header files used by the source files in `src/`.
Each file declares interfaces, structures, constants, and helper functions for a
specific module of the PM Nexus project.

## Header files overview

| File | Purpose |
|------|---------|
| `constants.h` | Defines global constants, macros, and configuration values used across the project. |
| `dns_server.h` | Declares the DNS server interface used during Access Point mode for captive portal and configuration. |
| `ethernet.h` | Declares Ethernet connectivity helpers and status checks for optional wired networking. |
| `import_libs.h` | Includes all required library headers and project-level header dependencies in a single place. |
| `led.h` | Declares LED initialization and status helper functions for device feedback. |
| `mqtt.h` | Declares MQTT client interfaces, initialization, reconnection, and publish helpers. |
| `sensors.h` | Declares sensor initialization and measurement routines for BME280 and PM2.5 sensors. |
| `sleep.h` | Declares deep sleep and power management functions. |
| `spiffs_utils.h` | Declares SPIFFS configuration storage functions and utilities. |
| `web_server.h` | Declares the web server endpoints and setup used for device configuration. |
| `wifi_utils.h` | Declares WiFi setup, connection management, and Access Point mode helpers. |

## How these headers are used

- `src/main.cpp` includes `import_libs.h`, which pulls in the shared declarations from these headers.
- Each source module in `src/` includes the corresponding header to access function prototypes and data structures.
- This structure keeps the code modular and easier to maintain.

## Recommended use

When adding new functionality, create a header file in this folder for the public API of the new module. Keep implementation details in the corresponding `.cpp` file in `src/`.

## Notes

- Header files should use include guards or `#pragma once` to avoid multiple inclusion.
- This README is focused on the current `include/` directory contents and their responsibilities.
