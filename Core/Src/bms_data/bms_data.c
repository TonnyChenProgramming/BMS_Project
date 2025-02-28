// bms_data.c
#include "bms_data.h"
#include "constants.h"
#include <string.h>
BMS_Data_t BMS_Data;  // <<<< GLOBAL DEFINITION
BMS_Data_t BMS_Data_Received;
void BMS_Init(void) {
    memset(&BMS_Data, 0, sizeof(BMS_Data));
    strcpy(BMS_Data.batteryName, BATTERY_NAME);
    BMS_Data.nominalVoltage_mV = NOMINAL_VOLTAGE_MV;
    BMS_Data.nominalCapacity_mAh = BATTERY_CAPACITY_MAH;
    BMS_Data.maxChargeCurrent_mA = MAXIMUM_CHARGE_CURRENT_MA;
    BMS_Data.maxBatteryVoltage_mV = MAXIMUM_VOLTAGE_MV;
    BMS_Data.minBatteryVoltage_mV = MINIMUM_VOLTAGE_MV;
    BMS_Data.temperatureLowerBound_C = CHARGING_TEMPERATURE_MINIMUM_C;
    BMS_Data.temperatureUpperBound_C = CHARGING_TEMPERATURE_MAXIMUM_C;

}
void BMS_Data_Received_Init(void)
{
	memset(&BMS_Data_Received, 0, sizeof(BMS_Data));
}
void BMS_SaveToEEPROM(void)
{
	   uint8_t buffer[16]; // each page contains up to 16 bytes, prevent page wrap-around

	    // To keep track of the device address
	    // Because Bit3,2,1 depend on A10, A9, A8
	    uint8_t current_devblockaddress = 0;

	    // ================Block 0: Battery Information==================
	    current_devblockaddress = EEPROM_WRITE_ADDRESS(0);

	    // ================== First Page: First 10 Characters ==================
	    memset(buffer, 0, 16);
	    memcpy(buffer, BMS_Data.batteryName, 10);
	    EEPROM_WritePage(current_devblockaddress, 0x00, buffer, 10);

	    // ================== Second Page: Last 16 Characters ==================
	    memcpy(buffer, BMS_Data.batteryName + 10, 16);
	    EEPROM_WritePage(current_devblockaddress, 0x10, buffer, 16);

	    // ================== Third Page: Remaining Battery Information ==================
	    memset(buffer, 0, 16);
	    memcpy(buffer, &BMS_Data.nominalVoltage_mV, 2);
	    memcpy(buffer + 2, &BMS_Data.nominalCapacity_mAh, 2);
	    memcpy(buffer + 4, &BMS_Data.maxChargeCurrent_mA, 2);
	    memcpy(buffer + 6, &BMS_Data.maxBatteryVoltage_mV, 2);
	    memcpy(buffer + 8, &BMS_Data.minBatteryVoltage_mV, 2);
	    memcpy(buffer + 10, &BMS_Data.temperatureLowerBound_C, 1);
	    memcpy(buffer + 11, &BMS_Data.temperatureUpperBound_C, 1);
	    EEPROM_WritePage(current_devblockaddress, 0x20, buffer, 16);

	    // ================== Block 1: Measurements ==================
	    current_devblockaddress = EEPROM_WRITE_ADDRESS(1);
	    memset(buffer, 0, 16);
	    memcpy(buffer, &BMS_Data.averageVoltage_mV, 2);
	    memcpy(buffer + 2, &BMS_Data.averageCurrent_mA, 2);
	    memcpy(buffer + 4, &BMS_Data.averageTemperature_C, 1);
	    memcpy(buffer + 5, &BMS_Data.averagePower_mW, 2);
	    EEPROM_WritePage(current_devblockaddress, 0x00, buffer, 16);

	    // ================== Block 2: State of Charge & Health ==================
	    current_devblockaddress = EEPROM_WRITE_ADDRESS(2);
	    memset(buffer, 0, 16);
	    memcpy(buffer, &BMS_Data.stateOfCharge_percent, 1);
	    memcpy(buffer + 1, &BMS_Data.stateOfHealth_percent, 1);
	    EEPROM_WritePage(current_devblockaddress, 0x00, buffer, 16);

	    // ================== Block 3: Lifetime Statistics ==================
	    current_devblockaddress = EEPROM_WRITE_ADDRESS(3);
	    memset(buffer, 0, 16);
	    memcpy(buffer, &BMS_Data.totalEnergyCharged_mWh, 2);
	    memcpy(buffer + 2, &BMS_Data.maxVoltage_mV, 2);
	    memcpy(buffer + 4, &BMS_Data.maxCurrent_mA, 2);
	    memcpy(buffer + 6, &BMS_Data.maxTemperature_C, 2);
	    memcpy(buffer + 8, &BMS_Data.totalChargingTime_seconds, 2);
	    memcpy(buffer + 10, &BMS_Data.totalChargeCycles, 1);
	    EEPROM_WritePage(current_devblockaddress, 0x00, buffer, 16);

	    // ================== Block 4: Flags & Counters ==================
	    current_devblockaddress = EEPROM_WRITE_ADDRESS(4);
	    memset(buffer, 0, 16);
	    memcpy(buffer, &BMS_Data.fault_flag, 1);
	    memcpy(buffer + 1, &BMS_Data.charge_up_flag, 1);
	    EEPROM_WritePage(current_devblockaddress, 0x00, buffer, 16);

	    // ================== Block 5: Checksum ==================
	    current_devblockaddress = EEPROM_WRITE_ADDRESS(5);
	    memset(buffer, 0, 16);
	    memcpy(buffer, &BMS_Data.checksum, 2);
	    EEPROM_WritePage(current_devblockaddress, 0x00, buffer, 16);
}
void BMS_LoadFromEEPROM(void)
{
    uint8_t buffer[16]; // 16-byte page buffer
    uint8_t current_devblockaddress = 0;

    // ================ Block 0: Battery Information ==================
    current_devblockaddress = EEPROM_WRITE_ADDRESS(0);

    // ========== First Page: First 10 Characters of batteryName ==========
    EEPROM_ReadPage(current_devblockaddress, 0x00, buffer, 10);
    memcpy(BMS_Data_Received.batteryName, buffer, 10);

    // ========== Second Page: Last 16 Characters of batteryName ==========
    EEPROM_ReadPage(current_devblockaddress, 0x10, buffer, 16);
    memcpy(BMS_Data_Received.batteryName + 10, buffer, 16);

    // ========== Third Page: Remaining Battery Information ==========
    EEPROM_ReadPage(current_devblockaddress, 0x20, buffer, 16);
    memcpy(&BMS_Data_Received.nominalVoltage_mV, buffer, 2);
    memcpy(&BMS_Data_Received.nominalCapacity_mAh, buffer + 2, 2);
    memcpy(&BMS_Data_Received.maxChargeCurrent_mA, buffer + 4, 2);
    memcpy(&BMS_Data_Received.maxBatteryVoltage_mV, buffer + 6, 2);
    memcpy(&BMS_Data_Received.minBatteryVoltage_mV, buffer + 8, 2);
    memcpy(&BMS_Data_Received.temperatureLowerBound_C, buffer + 10, 1);
    memcpy(&BMS_Data_Received.temperatureUpperBound_C, buffer + 11, 1);

    // ================ Block 1: Measurements ==================
    current_devblockaddress = EEPROM_WRITE_ADDRESS(1);
    EEPROM_ReadPage(current_devblockaddress, 0x00, buffer, 16);
    memcpy(&BMS_Data_Received.averageVoltage_mV, buffer, 2);
    memcpy(&BMS_Data_Received.averageCurrent_mA, buffer + 2, 2);
    memcpy(&BMS_Data_Received.averageTemperature_C, buffer + 4, 1);
    memcpy(&BMS_Data_Received.averagePower_mW, buffer + 5, 2);

    // ================ Block 2: State of Charge & Health ==================
    current_devblockaddress = EEPROM_WRITE_ADDRESS(2);
    EEPROM_ReadPage(current_devblockaddress, 0x00, buffer, 16);
    memcpy(&BMS_Data_Received.stateOfCharge_percent, buffer, 1);
    memcpy(&BMS_Data_Received.stateOfHealth_percent, buffer + 1, 1);

    // ================ Block 3: Lifetime Statistics ==================
    current_devblockaddress = EEPROM_WRITE_ADDRESS(3);
    EEPROM_ReadPage(current_devblockaddress, 0x00, buffer, 16);
    memcpy(&BMS_Data_Received.totalEnergyCharged_mWh, buffer, 2);
    memcpy(&BMS_Data_Received.maxVoltage_mV, buffer + 2, 2);
    memcpy(&BMS_Data_Received.maxCurrent_mA, buffer + 4, 2);
    memcpy(&BMS_Data_Received.maxTemperature_C, buffer + 6, 2);
    memcpy(&BMS_Data_Received.totalChargingTime_seconds, buffer + 8, 2);
    memcpy(&BMS_Data_Received.totalChargeCycles, buffer + 10, 1);

    // ================ Block 4: Flags & Counters ==================
    current_devblockaddress = EEPROM_WRITE_ADDRESS(4);
    EEPROM_ReadPage(current_devblockaddress, 0x00, buffer, 16);
    memcpy(&BMS_Data_Received.fault_flag, buffer, 1);
    memcpy(&BMS_Data_Received.charge_up_flag, buffer + 1, 1);

    // ================ Block 5: Checksum ==================
    current_devblockaddress = EEPROM_WRITE_ADDRESS(5);
    EEPROM_ReadPage(current_devblockaddress, 0x00, buffer, 16);
    memcpy(&BMS_Data_Received.checksum, buffer, 2);
}

