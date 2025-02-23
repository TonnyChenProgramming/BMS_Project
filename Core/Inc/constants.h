
#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#define BATTERY_NAME "18650 lithium-ion battery"
#define BATTERY_CAPACITY_MAH 1800 //Battery Capacity: 1800mAh
#define BATTERY_CAPACITY_MWH 6300 // Battery capacity: 6300mWh
#define NOMINAL_VOLTAGE 3700//Nominal Voltage: 3.7V (3700mV) – Average operating voltage.
#define MINIMUM_VOLTAGE 2750//Minimum Voltage (Discharge Cutoff): 2.75V (2750mV) – Prevents over-discharge.
#define MAXIMUM_VOLTAGE 4200//Maximum Voltage (Charge Cutoff): 4.2V (4200mV) – Prevents overcharging.
#define MAXIMUM_CHARGE_CURRENT 1800//Maximum Charge Current: 1.8A (1800mA) – Safe charging limit.
#define CHARGING_TEMPERATURE_MINIMUM 0//Operating Temperature Range:
#define CHARGING_TEMPERATURE_MAXIMUM 45 //Charging: 0°C to 45°C
#define SHORT_CIRCUIT_CURRENT_THRESHOLD 5000 // 500mA
#define SHORT_CIRCUIT_VOLTAGE_THRESHOLD 3000 // 3mV
#define TIME_INTERVAL 0.8
#endif
