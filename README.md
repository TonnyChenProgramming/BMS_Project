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

<img width="692" height="392" alt="image" src="https://github.com/user-attachments/assets/c217356d-dcca-4623-acdb-66be682c279c" />
<img width="692" height="250" alt="image" src="https://github.com/user-attachments/assets/f46c70d4-ebe8-44e8-aa7b-7d07b240bf83" />


### 🪛 1. Hardware Layer – Physical Interface & Sensing


<img width="692" height="392" alt="image" src="https://github.com/user-attachments/assets/7970520d-5623-4b71-b136-303bf5ae3560" />![hardwareImage](https://github.com/user-attachments/assets/20893ba3-f8e3-4bd0-a3c0-462a59af3dd4)


This layer includes all physical components that sense electrical signals, display system status, and control charging behavior. It forms the foundation of the entire Battery Management System (BMS).
____________________________________________________________________________

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

____________________________________________________________________________


#### ⚡ Power Distribution

##### 🔋 Battery Charging

-TP4050 module charges only the 18650 battery

-Charging current is monitored via ACS712

##### ⚡ System Supply (3.3V)

-STM32, sensors, display, buzzer, and Wi-Fi module powered by STM32 onboard LDO regulator

-LDO is fed from the DC rail or battery, ensuring system remains operational when charging or running standalone
____________________________________________________________________________


#### ❌ Design Trade-Off
##### EEPROM (AT24C16) Excluded

-Initially planned for persistent data logging (e.g. charge cycles, runtime)

Removed due to I2C bus congestion and hardware layout constraints


_____________________________________________________________________________
### 2.💻 Firmware Layer – data acquisition and computation 
This layer runs on the STM32F407 microcontroller and is responsible for data acquisition, control logic, and real-time task management. It orchestrates all sensor readings, computations, and communications using FreeRTOS.
_____________________________________________________________________________
### 2.1 STM32 HAL Code
<img width="653" height="403" alt="image" src="https://github.com/user-attachments/assets/c4deeb28-6682-4826-bbe5-7bd2d2a30edd" />

#### 🔹 Core Features
##### Dual ADC Sampling via DMA

-Simultaneously samples battery voltage and charging current using two ADC channels with DMA.

-Ensures efficient, non-blocking data collection.

##### Periodic Temperature Monitoring

-Reads NTC thermistor every 10 seconds.

-Used for thermal safety control and display updates.

##### Real-time SoC and SoH Computation

-Calculates State of Charge (%) and estimates State of Health (%) based on usage history.

-Logic executed in a dedicated processing task.

##### OLED Display Output (I2C)

-Displays live system stats like voltage, current, temperature, SoC, SoH, and fault flags.

-Display refreshes are throttled to avoid I2C bus congestion.

##### Fault Detection and Buzzer Alerts

-Continuously checks for abnormal conditions (e.g., over-temp, short circuit).

-Triggers buzzer and safety logic when necessary.

##### UART Output (JSON Format)

-Periodically sends system status to ESP8266 via UART in JSON format.

-Enables seamless cloud integration.

##### FreeRTOS Multitasking
<img width="692" height="392" alt="image" src="https://github.com/user-attachments/assets/82c0310c-8322-4758-95c9-7c49f9837e2e" />


Tasks separated by functionality:

-SamplingTask for ADC + temperature

-ProcessTask for SoC/SoH computation

-DisplayTask for OLED

-UploadTask for UART output

-BuzzerTask for audible alerts

Shared data protected using xSemaphore
_____________________________________________________________________________
### 🔌 2.2 ESP8266 NodeMCU Arduino Code
The ESP8266 NodeMCU acts as the Wi-Fi bridge between the STM32 microcontroller and the Firebase Realtime Database.

#### ✅ Key Functions
##### UART Listener
-Listens to JSON-formatted data from STM32 over Serial.

#### Firebase Push
-Parses the received JSON and uploads it to a specified node in Firebase Realtime Database.

#### Wi-Fi Connection Handling
-Automatically connects to the specified Wi-Fi SSID and password on startup.
-Includes basic reconnection logic to maintain uptime.

#### Efficient Upload Control
-Only pushes data when new data is received or when a manual upload is triggered (optional future feature).

#### ⚙️ Tools & Libraries Used
-ESP8266WiFi.h for Wi-Fi communication

-FirebaseESP8266.h for Realtime Database integration

-ArduinoJson.h for decoding STM32 JSON messages

________________________________________________________________________________

### 📱 3. Software Layer — Android App (Kotlin + Firebase)

<img width="473" height="301" alt="image" src="https://github.com/user-attachments/assets/a1df82b9-df43-4039-a13a-79dc5980b9d2" />

<img width="371" height="287" alt="image" src="https://github.com/user-attachments/assets/1acc27c7-b886-4dd3-8922-f89cd27ef465" />


The Android app provides a real-time, user-friendly interface for monitoring the battery system remotely via Firebase.

#### ✅ Key Functions
##### Live Data Display
-Automatically fetches the latest battery data from Firebase and updates the UI every second.

##### Human-Readable Interface
-Clearly displays:

-Battery name & status

##### SoC (State of Charge) and SoH (State of Health)

-Voltage, current, temperature

-Charging time and cycles

-Fault and charge-up flags

##### Error Handling
-Implements OnDataReceivedListener interface to handle Firebase fetch success/failure callbacks with proper UI messaging.

##### 📦 Tools & Libraries Used
-Firebase Realtime Database for cloud backend

-ViewBinding for efficient and type-safe UI updates

-Handler + Runnable for periodic polling

-Android Studio + Kotlin as development stack

##### 🧩 App Architecture Overview
-MainActivity.kt handles lifecycle & UI updates

-FirebaseManager.kt abstracts Firebase data access

-Uses a listener pattern to decouple networking from UI logic

________________________________________________________________________________
## 📂 Directory Structure

<img width="320" height="150" alt="image" src="https://github.com/user-attachments/assets/735b6396-b539-45c2-b545-fee1469f85c3" />

### ✅ What’s Inside
Firmware/: Contains your STM32CubeIDE project with FreeRTOS integration and all STM32-specific code.

ESP8266_Firmware/: Arduino sketch for the NodeMCU to receive UART data and push it to Firebase.

AndroidApp/: Android Studio project that listens to Firebase and updates UI.

Docs/: Place architecture diagrams, flowcharts, and any helpful visuals here.

README.md: This file — the central documentation hub for your project.



