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
<img width="416" height="220" alt="image" src="https://github.com/user-attachments/assets/7f5b60c6-4ada-4241-9b48-4a95cb337184" />
