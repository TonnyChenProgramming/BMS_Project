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


This layer includes all physical components that sense electrical signals, display system status, and control charging behavior. It forms the foundation of the entire Battery Management System (BMS).

#### ✨ Key Components

##### 🔌 ACS712 Current Sensor

-Measures charging current via Hall effect

-Sends analog output to STM32 ADC for sampling

##### 🔻 Voltage Divider

-Steps down battery voltage to safe levels (<3.3V)

-Enables direct connection to STM32 ADC

##### 🌡️ NTC Thermistor (10kΩ)

-Detects battery surface temperature

-Outputs analog voltage proportional to temperature

##### 🖥️ OLED Display (I2C)

-Shows real-time stats: voltage, current, SoC, SoH, temperature

##### 🔘 Open-Drain Push Button

-Triggers manual data upload or reset

-Connected to GPIO with internal pull-up

##### 🔊 Buzzer

-Emits alert sounds on over-temperature or fault conditions

##### ⚙️ TP4050 Charging Module

-Charges 18650 battery via USB Type-C

-Battery is the only component connected to this charger

##### 🔋 18650 Battery + Holder

-Provides main power storage

-Connected through current sensor and voltage divider

##### 📶 ESP8266 NodeMCU Wi-Fi Module

-Communicates with STM32 via UART

-Pushes data to Firebase Realtime Database

-Enables real-time mobile monitoring via custom Android app

####⚡ Power Distribution

#####🔋 Battery Charging

-TP4050 module charges only the 18650 battery

-Charging current is monitored via ACS712

#####⚡ System Supply (3.3V)

-STM32, sensors, display, buzzer, and Wi-Fi module powered by STM32 onboard LDO regulator

-LDO is fed from the DC rail or battery, ensuring system remains operational when charging or running standalone

#### ❌ Design Trade-Off
##### EEPROM (AT24C16) Excluded

-Initially planned for persistent data logging (e.g. charge cycles, runtime)

Removed due to I2C bus congestion and hardware layout constraints



