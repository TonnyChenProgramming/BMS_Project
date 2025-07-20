// constants.h

#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// Battery Information
#define BATTERY_NAME "18650 lithium-ion battery"
#define BATTERY_CAPACITY_MAH 1800       // Battery Capacity: 1800mAh
#define BATTERY_CAPACITY_MWH 6300       // Battery Capacity: 6300mWh
#define NOMINAL_VOLTAGE_MV 3700         // Nominal Voltage: 3.7V (3700mV) – Average operating voltage
#define MINIMUM_VOLTAGE_MV 2750         // Minimum Voltage (Discharge Cutoff): 2.75V (2750mV) – Prevents over-discharge
#define MAXIMUM_VOLTAGE_MV 4200         // Maximum Voltage (Charge Cutoff): 4.2V (4200mV) – Prevents overcharging
#define MAXIMUM_CHARGE_CURRENT_MA 1800  // Maximum Charge Current: 1.8A (1800mA) – Safe charging limit

// Operating Temperature Range (°C)
#define CHARGING_TEMPERATURE_MINIMUM_C 0
#define CHARGING_TEMPERATURE_MAXIMUM_C 45

// Safety Thresholds
#define SHORT_CIRCUIT_CURRENT_THRESHOLD_MA 5000 // Short-circuit current threshold: 5000mA
#define SHORT_CIRCUIT_VOLTAGE_THRESHOLD_MV 3000 // Short-circuit voltage threshold: 3000mV

// Time Interval (Seconds) for Power Calculation
#define TIME_INTERVAL_S 0.8

#endif // __CONSTANTS_H
