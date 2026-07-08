# IoT-Based Smart Water Softener

> An ESP32-based IoT smart water softener monitoring and control system with a live web dashboard, MQTT communication, and a modular firmware architecture.

> **Note:** This project was originally developed as part of an IoT Engineer evaluation and then expanded into a complete end-to-end project.

## Project Overview

This project demonstrates a complete IoT pipeline from an embedded device to a cloud-connected dashboard.

The ESP32 collects simulated sensor data, connects to Wi-Fi automatically, publishes telemetry to HiveMQ Cloud, receives remote commands, and updates a live dashboard through a Node.js backend.

The firmware is written as a modular PlatformIO project to resemble a real embedded software architecture.

## Features

- ESP32 firmware using PlatformIO
- Automatic Wi-Fi connection
- Secure MQTT communication
- Live telemetry dashboard
- Remote valve control
- Remote regeneration control
- Automatic regeneration timer
- Safety checks before regeneration
- Device state machine
- Live alerts
- WebSocket-based dashboard updates
- Random sensor simulation
- Hardcoded sensor values for edge-case testing

## Hardware

- ESP32 Dev Module
- Wi-Fi Network

### Sensor Simulation

This project intentionally uses simulated sensors.

- Random values simulate normal operation.
- Hardcoded values are used to verify edge cases like low pressure, low salt, regeneration requests, and safety conditions.

This allowed testing all firmware logic without physical sensors.

## Software Stack

### Firmware
- C++
- PlatformIO
- Arduino Framework
- WiFiClientSecure
- PubSubClient

### Backend
- Node.js
- Express
- MQTT.js
- WebSocket

### Dashboard
- HTML
- CSS
- JavaScript

### Cloud
- HiveMQ Cloud

## Architecture

```text
                 WiFi
                   |
                   v
          HiveMQ Cloud Broker
             ^            |
             |            v
          ESP32 <---- Node.js Backend
             |            |
             +------> Dashboard
```

## Folder Structure

```text
ecowell-smart-softener
├── backend/
│   ├── public/
│   ├── src/
│   └── package.json
├── include/
├── lib/
├── src/
│   ├── app/
│   ├── config/
│   ├── logger/
│   ├── mqtt/
│   ├── sensor/
│   ├── state_machine/
│   ├── wifi/
│   └── main.cpp
├── test/
├── platformio.ini
└── README.md
```

## Device States

- IDLE
- MONITORING
- REGENERATION_REQUIRED
- REGENERATING
- FAULT

## MQTT Topics

Telemetry

```
ecowell/softener/data
```

Commands

```
ecowell/softener/cmd
```

## Dashboard

Displays:

- Flow Rate
- Pressure
- Salt Level
- TDS
- Wi-Fi Status
- Power Status
- Device State
- Valve Status
- Regeneration Status
- Alerts
- Last Updated

## Screenshots

## Dashboard

![Dashboard](images/Dashboard.png)
![Dashboard](images/Dashboard2.png)


## Serial Monitor

![Serial Monitor](images/Serial_Monitor.png)
![Serial Monitor](images/Serial_Monitor2.png)


## Code File

![Code File](images/Code_File.png)


-----------------------------------------------------------------------

### Video Demonstration

[![Watch Demo](https://img.youtube.com/vi/xP2obVV_vCo/maxresdefault.jpg)](https://www.youtube.com/watch?v=xP2obVV_vCo)

▶ Click the image above to watch the full demo video on YouTube.

-----------------------------------------------------------------------

## Running

### Firmware

```bash
pio run
pio run --target upload
pio device monitor
```

### Backend

```bash
cd backend
npm install
node src/server.js
```

Open:

```
http://localhost:3000
```

## Assignment Coverage

- Sensor monitoring
- State machine
- MQTT communication
- Remote command execution
- Live dashboard
- Alerts
- Regeneration workflow
- Safety validation
- ESP32 implementation
- Modular firmware

## Future Improvements

- OTA updates
- Real sensors
- Database logging
- Charts
- Mobile app

## Author

**Md Kashif Alam**

GitHub:
https://github.com/KashifAlam407

LinkedIn:
https://www.linkedin.com/in/md-kashif-alam-a55b19380/
