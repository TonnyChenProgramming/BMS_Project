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


🧩 Components
Component	Function
ACS712 Current Sensor	Measures the battery’s charging current using the Hall effect. Outputs analog voltage to MCU.
Voltage Divider	Reduces battery voltage to an STM32-safe ADC input range.
NTC Thermistor	Detects ambient or battery temperature and feeds analog signal to STM32 ADC.
OLED Display (I2C)	Displays system metrics like SoC, current, voltage, and status indicators.
Open-Drain Push Button	Allows manual interaction for triggering uploads or resets.
Buzzer	Emits alarms when faults or abnormal conditions (e.g., overtemp) are detected.
TP4050 Charging Module	Provides regulated charging from USB Type-C to the lithium battery.
Battery Holder	Houses 18650 Li-ion cell(s) under monitoring and charge control.

❌ Note: EEPROM (AT24C16) was originally planned for persistent metric storage (e.g., total charge time/cycles), but has been removed from the system due to hardware limitations.

🔌 Power and Signal Flow
DC Power Rail: A single regulated DC line from the TP4050 supplies power to the STM32 and all peripherals.

Analog Signals: Current (V_current), voltage (V_voltage), and temperature (V_temp) values are sent to STM32 ADC pins.

I2C Bus: Used for OLED communication.

GPIO/UART:

UART connects to the Wi-Fi module.

GPIO controls the buzzer and reads push button input.

📋 Summary
This hardware stack achieves:

Accurate real-time sensing of battery parameters.

Visual and audible feedback for end users.

Clean modular charging and protection architecture.

Simplification of the design by removing EEPROM to prioritize stability and available I2C bandwidth.


