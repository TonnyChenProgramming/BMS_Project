// bms_data.c
#include "bms_data.h"
#include "constants.h"
#include <string.h>
BMS_Data_t BMS_Data;  // <<<< GLOBAL DEFINITION

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
    BMS_Data.stateOfHealth_percent = 95; // assume the battery with a SOH of 95% as default
    BMS_Data.totalChargingTime_seconds = 0;

}
