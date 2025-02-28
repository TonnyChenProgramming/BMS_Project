#ifndef BMS_DATA_H
#define BMS_DATA_H

#include <stdint.h>
#include "eeprom_processings.h"
#define BATTERY_NAME_MAX_LEN 26
#define PAGE_SIZE 16

// ============================= EEPROM DEVICE ADDRESS =============================
// AT24C16 EEPROM uses 7-bit I2C address: 1010 A2 A1 A0 R/W
// Bits A2, A1, A0 select the block number (0-7) and are combined with base address
// - Write Base: 0xA0 (1010 0000) + (Block number << 1)
// - Read Base:  0xA1 (1010 0001) + (Block number << 1)
// Example: Block 0 Write: 0xA0, Block 1 Write: 0xA2, Block 2 Write: 0xA4, etc.

#define DEVADDRESS_WRITE_BASE 0xA0 // Base address for WRITE operations (Block 0)
#define DEVADDRESS_READ_BASE  0xA1 // Base address for READ operations (Block 0)

// Use these macros to generate device address for specific blocks
#define EEPROM_WRITE_ADDRESS(block) (DEVADDRESS_WRITE_BASE | ((block & 0x07) << 1))
#define EEPROM_READ_ADDRESS(block)  (DEVADDRESS_READ_BASE  | ((block & 0x07) << 1))

// Example Usage:
// uint8_t address = EEPROM_WRITE_ADDRESS(2); // Block 2 Write: 0xA4
// uint8_t address = EEPROM_READ_ADDRESS(3);  // Block 3 Read: 0xA7

// ============================= BMS DATA STRUCTURE =============================

// BMS Data Structure
typedef struct {
    // Battery Information
    char batteryName[BATTERY_NAME_MAX_LEN];
    uint16_t nominalVoltage_mV;
    uint16_t nominalCapacity_mAh;
    uint16_t maxChargeCurrent_mA;
    uint16_t maxBatteryVoltage_mV;
    uint16_t minBatteryVoltage_mV;
    int8_t temperatureLowerBound_C;
    int8_t temperatureUpperBound_C;

    // Measurements
    uint16_t averageVoltage_mV;
    uint16_t averageCurrent_mA;
    uint8_t averageTemperature_C;
    uint16_t averagePower_mW;

    // State of Charge & Health
    uint8_t stateOfCharge_percent;
    uint8_t stateOfHealth_percent;

    // Lifetime Statistics
    uint16_t totalEnergyCharged_mWh;
    uint16_t maxVoltage_mV;
    uint16_t maxCurrent_mA;
    uint16_t maxTemperature_C;
    uint16_t totalChargingTime_seconds;
    uint8_t totalChargeCycles; //?

    // Flags and Counters
    uint8_t fault_flag;
    uint8_t charge_up_flag;

    // Checksum
    uint16_t checksum; //?
} BMS_Data_t;

extern BMS_Data_t BMS_Data;

// BMS data Function
void BMS_Init(void);
void BMS_Data_Received_Init(void);

// EEPROM Functions
void BMS_SaveToEEPROM(void);
void BMS_LoadFromEEPROM(void);


#endif // BMS_DATA_H


