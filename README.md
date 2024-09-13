# Plant Irrigation System with Solar Panel and Blynk App

## Project Description

This project is an automated plant irrigation system powered by a solar panel and integrated with the IoT application, Blynk. The system uses soil moisture sensors, voltage sensors, and current sensors to monitor soil moisture levels and battery voltage. Based on the data received from the sensors, the system controls relays to activate the water pump and solenoid valves, ensuring the plants are watered according to their needs.

## Hardware Specifications

- **Board**: ESP32 Dev Module
- **Inputs**: Soil Moisture Sensor, Voltage Sensor, Current Sensor (ACS712)
- **Outputs**: Blynk (mobile app), LCD, Relay
- **Power Source**: Solar Panel
- **Main Components**:
  - 4-Channel Relay
  - 3 Soil Moisture Sensors
  - 2 Voltage Sensors
  - 2 Current Sensors (ACS712)
  - 2 LCDs (I2C Address 0x27 and 0x21)

## ESP32 Pin Connections

| Component              | GPIO Pin |
| ---------------------- | -------- |
| Soil Moisture Sensor 1 | 14       |
| Soil Moisture Sensor 2 | 33       |
| Soil Moisture Sensor 3 | 32       |
| Voltage Sensor 1       | 36       |
| Voltage Sensor 2       | 39       |
| Current Sensor 1       | 34       |
| Current Sensor 2       | 35       |
| Relay 1 (Water Pump)   | 25       |
| Relay 2 (Solenoid 1)   | 26       |
| Relay 3 (Solenoid 2)   | 4        |
| Relay 4 (Solenoid 3)   | 2        |

## Blynk Connection

- **Blynk Auth Token**: Replace with your Blynk token.
- **WiFi SSID**: Replace with your WiFi SSID.
- **WiFi Password**: Replace with your WiFi password.

```cpp
char auth[] = "YourBlynkAuthToken";
char ssid[] = "YourSSID";
char pass[] = "YourPassword";
```

## Calibration Values

The following calibration values are used to adjust sensor accuracy. These values can be modified based on actual measurements with a multimeter:

```cpp
int calibration1 = 3218; // (ACS Sensor 1) Calibration depending on vacs and load
int calibration2 = 3218; // (ACS Sensor 2) Calibration depending on vacs and load
```

## Project Functionality

- Soil Moisture Measurement: The system uses three soil moisture sensors to detect soil moisture levels. If the moisture level drops below a set threshold, the corresponding relay is activated to water the plants.
- Voltage Measurement: The system monitors the voltage of two batteries using voltage sensors and displays the readings on both the Blynk app and physical LCDs.
- Current Measurement: Current sensors (ACS712) measure the current flowing through the system, which is also displayed on the Blynk app and LCDs.

## LCD Integration

- The system uses two I2C LCDs to display the voltage and current measurements of the batteries. These LCDs are initialized with the addresses 0x27 and 0x21.

## Usage Instructions

1. Configure Blynk: Replace the auth, ssid, and pass variables in the code with your Blynk token, WiFi SSID, and WiFi password.
2. Wiring: Ensure all sensors and relays are correctly connected to the ESP32 according to the pin configuration provided.
3. Power Supply: The system is powered by a solar panel, and the ESP32 is connected to the battery that is charged by the panel.
4. Run the System: Upload the code to the ESP32, and the system will start monitoring soil moisture and voltage levels, automatically controlling the irrigation system based on sensor readings.

- This project automates plant watering by integrating IoT technology, making it easy to monitor and control via the Blynk mobile app.
