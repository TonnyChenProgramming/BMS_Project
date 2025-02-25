#include <processings.h>
#include "constants.h"
#include "sensing.h"
#include "main.h"
#include "bms_data.h"


float power = 0;
Time_t time_pack = {0};

static float previous_voltage = 0.0; // determine the state of battery charging/idle
static float same_voltage_counter = 0;
static int number_of_sample = 0;
static float energyAccumulator = 0.0f;
static uint8_t total_charging_time_counter = 0;

static uint8_t tracker = 0;

// Function Declarations

// Internal Helper Functions
static int calculate_soc(void);
static int calculate_soh(void);
static inline float calculate_power();
static void calculate_remaining_time(void);
static void determine_status(void);

// Average Calculations
static inline uint16_t calculate_average_voltage(void);
static inline uint16_t calculate_average_current(void);
static inline uint8_t calculate_average_temperature(void);
static inline uint16_t calculate_average_power(void);
static void calculate_total_energy_charged(void);

// Tracking and Fault Detection
static void track_maximum_voltage_current_temperature(void);
static void record_total_charging_time(void);
static void detect_overvoltage(void);
static void detect_undervoltage(void);
static void detect_overcurrent(void);
static void detect_short_circuit(void);


// Main Processing Function
void processing(void);


//soh wrong triggered. soc miscalcualted after the voltage spike.current is 0 A?
void processing(void)
{
	determine_status();
	// oled requires voltage, current, soc, power, temperature, soh, status, hours, minutes
	if ((batteryStatus == IDLE || batteryStatus == FULL)&&power < 0.5)
	{
		BMS_Data.stateOfCharge_percent = calculate_soc();
	}
	if (batteryStatus == FULL && (!BMS_Data.charge_up_flag))
	{
		BMS_Data.charge_up_flag = 1;
		BMS_Data.stateOfHealth_percent = calculate_soh();
	}
	if (batteryStatus == CHARGING  &&  current > 50)
	{
		power = calculate_power();
		number_of_sample++;
		BMS_Data.averageVoltage_mV = calculate_average_voltage();
		BMS_Data.averageCurrent_mA = calculate_average_current();
		BMS_Data.averagePower_mW = calculate_average_power();
		BMS_Data.averageTemperature_C = calculate_average_temperature();
		calculate_total_energy_charged();
		record_total_charging_time();
		track_maximum_voltage_current_temperature();
		detect_overvoltage();
		detect_undervoltage();
		detect_overcurrent();
		detect_short_circuit();


		if (++tracker >=100)
		{
			tracker = 0;
		}
	}

	calculate_remaining_time();
}

void determine_status(void)
{
	// this function is used to determine the status of the battery, either in charging/full/idle
	// if voltage difference is positive, then it is charging, otherwise, idel
	if (voltage - previous_voltage >= 75 ) // current voltage is 0.01V greater than the last voltage
	{
		batteryStatus = CHARGING;
		same_voltage_counter = 0;
	}
	//if no voltage variation, very low power(cause by noise)
	else if (voltage-previous_voltage <50 && previous_voltage - voltage <50 && power < 0.5)//a noise buffer range
	{
		same_voltage_counter++;// if it is not continuously increasing, reset to zero
	}
	previous_voltage = voltage;

	if (same_voltage_counter >=13) // if the same voltage state last for 10s
	{
		if (voltage >=4150)
		{
			batteryStatus = FULL;
		}
		else
		{
			batteryStatus = IDLE;
		}
		same_voltage_counter = 0;
	}
	previous_voltage = voltage;
}
static int calculate_soc(void)
{
    int soc = (voltage - MINIMUM_VOLTAGE_MV) * 100 / (MAXIMUM_VOLTAGE_MV - MINIMUM_VOLTAGE_MV);
    if (soc < 0) soc = 0;
    if (soc > 100) soc = 100;
    return soc;
}
static int calculate_soh(void)
{
    if (current == 0.0f && voltage >= 4000.0f)  // Battery fully charged
    {
        // Example Formula: Compare maximum voltage with nominal voltage
    	uint8_t soh = (voltage / MAXIMUM_VOLTAGE_MV) * 100;

        // Ensure SOH is within 0-100%
        if (soh > 100) soh = 100;
        if (soh < 0) soh = 0;
        return soh;
    }
    else
    {
        return 0;  // Not fully charged, can't measure SOH
    }

}

static inline float calculate_power(void)
{
    return voltage/1000 * current/1000; // Convert mV and mA to W
}
static void calculate_remaining_time(void)
{
	if (batteryStatus == CHARGING && power > 0.5)
	{
		time_pack.secs = ((1.0-(float)BMS_Data.stateOfCharge_percent/100) *(float)BATTERY_CAPACITY_MWH/1000 * 3600) / power;
		time_pack.hours = time_pack.secs / 3600;
		time_pack.minutes = time_pack.secs % 3600 / 60;
	}
	else
	{
		time_pack.hours = 0;
		time_pack.minutes = 0;
	}

}
static inline uint16_t calculate_average_voltage(void)
{
	return BMS_Data.averageVoltage_mV + (voltage - BMS_Data.averageVoltage_mV) / number_of_sample;
}

static inline uint16_t calculate_average_current(void)
{
	return BMS_Data.averageCurrent_mA + (current - BMS_Data.averageCurrent_mA) / number_of_sample;
}

static uint8_t calculate_average_temperature(void)
{
	if (temperature > 10)
	{
		return BMS_Data.averageTemperature_C + (temperature - BMS_Data.averageTemperature_C) / number_of_sample;
	}
	else
	{
		return BMS_Data.averageTemperature_C;
	}

}

static inline uint16_t calculate_average_power(void)
{
	return BMS_Data.averagePower_mW + (calculate_power() * 1000 - BMS_Data.averagePower_mW) / number_of_sample;
}


static void calculate_total_energy_charged(void)
{
    energyAccumulator += power * TIME_INTERVAL_S * 1000.0f / 3600.0f;
    while (energyAccumulator >= 1.0f) {
        BMS_Data.totalEnergyCharged_mWh++;
        energyAccumulator -= 1.0f; // Remove the integer part
    }
}
static void track_maximum_voltage_current_temperature(void)
{
	if (voltage>BMS_Data.maxVoltage_mV)
	{
		BMS_Data.maxVoltage_mV = voltage;
	}
	if (current>BMS_Data.maxCurrent_mA)
	{
		BMS_Data.maxCurrent_mA = current;
	}
	if (temperature>BMS_Data.maxTemperature_C)
	{
		BMS_Data.maxTemperature_C = temperature;
	}
}
static void record_total_charging_time(void)
{

	if (++total_charging_time_counter >=5)
	{
		total_charging_time_counter =0;
		BMS_Data.totalChargingTime_seconds += 4;
	}
}
void update_total_charge_cycle(void)
{
	//read the total charged cycles
	//increment the charged cycles and update the eeprom
	return;
}
void detect_overvoltage(void)
{
	if (voltage > MAXIMUM_VOLTAGE_MV)
	{
		BMS_Data.fault_flag = 1;
	}
}
void detect_undervoltage(void)
{
	if (voltage < MINIMUM_VOLTAGE_MV)
	{
		BMS_Data.fault_flag = 1;
	}
}
void detect_overcurrent(void)
{
	if (current>MAXIMUM_CHARGE_CURRENT_MA)
	{
		BMS_Data.fault_flag = 1;
	}
}
void detect_short_circuit(void)
{
	if (voltage < SHORT_CIRCUIT_VOLTAGE_THRESHOLD_MV && current>SHORT_CIRCUIT_CURRENT_THRESHOLD_MA)
	{
		BMS_Data.fault_flag = 1;
	}
}
