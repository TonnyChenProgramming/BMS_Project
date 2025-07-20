# Battery Management System (FreeRTOS + STM32 + WiFi)
A real-time Battery Management System implemented on the STM32F407 Discovery board using FreeRTOS. This system continuously samples voltage, current, and temperature; computes state of charge (SoC) and state of health (SoH); detects faults; updates an OLED display; and transmits data over UART in JSON format.

## 📦 Features

- Dual ADC sampling using DMA (voltage & current)
- Periodic temperature monitoring
- State of Charge (SoC) and State of Health (SoH) computation
- OLED display output for live system stats
- Fault detection and buzzer alerts
- UART output (JSON format) for Wi-Fi module
- Wi-Fi integration via ESP8266
- Firebase Realtime Database push
- Android app for real-time monitoring
- Multi-tasking using FreeRTOS

## 🧭 System Architecture
The Battery Monitoring System is designed using a **layered abstraction architecture**, dividing the system into three key levels: **Hardware Layer**, **Firmware Layer**, and **Software Layer**. This modular structure ensures high cohesion within layers and low coupling between them, making the system robust, scalable, and easy to debug.

<img width="346" height="188" alt="image" src="https://github.com/user-attachments/assets/c217356d-dcca-4623-acdb-66be682c279c" />

### 🪛 1. Hardware Layer – Physical Interface & Sensing


<img width="591" height="380" alt="image" src="https://github.com/user-attachments/assets/7970520d-5623-4b71-b136-303bf5ae3560" />![hardwareImage](https://github.com/user-attachments/assets/20893ba3-f8e3-4bd0-a3c0-462a59af3dd4)


This layer includes all physical components that sense electrical signals, output system status, and manage charging. It forms the foundation of the entire Battery Management System (BMS).

Key Components
ACS712 Current Sensor

Measures real-time charging current via Hall effect.

Outputs analog voltage to STM32 ADC for current calculation.

Voltage Divider

Steps down battery voltage (<3.3V) for safe ADC sampling.

NTC Thermistor (10kΩ)

Senses battery surface temperature.

Converts temperature to analog voltage for STM32 ADC.

OLED Display (0.96", I2C)

Shows system status: voltage, current, SoC, SoH, and temperature.

Push Button (Open-Drain)

Triggers manual data upload or reset event.

Wired to STM32 GPIO with internal pull-up.

Buzzer

Sounds alerts on fault or over-temperature conditions.

TP4050 Charging Module

Charges a single 18650 Li-ion battery via USB Type-C.

Battery is only component charged through this module.

18650 Battery Holder

Houses and connects the battery for safe charging and monitoring.

ESP8266 NodeMCU Wi-Fi Module

Receives battery data via UART from STM32.

Pushes data to Firebase Realtime Database.

Connects wirelessly to mobile app for real-time monitoring.

Power Distribution
🔋 Battery Charging

The TP4050 module charges the 18650 battery only.

ACS712 sensor monitors charging current in real time.

⚡ System Power Supply

All components (STM32, sensors, display, Wi-Fi module, buzzer) are powered by the 3.3V output of STM32’s onboard LDO regulator.

The regulator draws from battery or external DC input to ensure continuous operation.

Design Note
❌ EEPROM (AT24C16) Removed

Originally planned for logging charge cycles and run time.

Removed due to I2C bus limitations and space constraints.




