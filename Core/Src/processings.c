#include <processings.h>
#include "constants.h"
#include "sensing.h"
#include "main.h"

struct Maximum {
    float voltage;
    float current;
    float temperature;
};

float power = 0;
int soc = 0;
int soh = 0;
int hours = 0;
int minutes = 0;
static int sec = 0;
static float previous_voltage = 0.0; // determine the state of battery charging/idle
static float same_voltage_counter = 0;

float average_power = 0;
int number_of_power_sample = 0;
float total_energy_charged = 0;
struct Maximum max = {0.0f,0.0f,0.0f};
int total_charging_time_counter = 0;
uint8_t fault_detected = 0;
// Declare functions
static int calculate_soc(void);
static int calculate_soh(void);
static inline float calculate_power(void);
static void calculate_remaining_time(void);
static void determine_status(void);
void processing(void);


// Function Declarations
static void calculate_average_power(void);
static void calculate_total_energy_charged(void);
static void track_maximum_voltage_current_temperature(void);
void record_total_charging_time(void);
void detect_overvoltage(void);
void detect_undervoltage(void);
void detect_overcurrent(void);
void detect_short_circuit(void);



//soh wrong triggered. soc miscalcualted after the voltage spike.current is 0 A?
void processing(void)
{
	determine_status();
	// oled requires voltage, current, soc, power, temperature, soh, status, hours, minutes
	if ((batteryStatus == IDLE || batteryStatus == FULL)&&power < 0.5)
	{
		soc = calculate_soc();
	}
	if (batteryStatus == FULL)
	{
		soh = calculate_soh();
	}
	if (batteryStatus == CHARGING  &&  current > 50)
	{
		power = calculate_power();
		calculate_average_power();
		calculate_total_energy_charged();
		track_maximum_voltage_current_temperature();
		total_charging_time_counter++;
		detect_overvoltage();
		detect_undervoltage();
		detect_overcurrent();
		detect_short_circuit();
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
    int soc = (voltage - MINIMUM_VOLTAGE) * 100 / (MAXIMUM_VOLTAGE - MINIMUM_VOLTAGE);
    if (soc < 0) soc = 0;
    if (soc > 100) soc = 100;
    return soc;
}
static int calculate_soh(void)
{
    if (current == 0.0f && voltage >= 4000.0f)  // Battery fully charged
    {
        // Example Formula: Compare maximum voltage with nominal voltage
        soh = (voltage / MAXIMUM_VOLTAGE) * 100;

        // Ensure SOH is within 0-100%
        if (soh > 100) soh = 100;
        if (soh < 0) soh = 0;
    }
    else
    {
        soh = 0;  // Not fully charged, can't measure SOH
    }
    return soh;
}

static inline float calculate_power(void)
{
    return voltage/1000 * current/1000; // Convert mV and mA to W
}
static void calculate_remaining_time(void)
{
	if (batteryStatus == CHARGING && power > 0.5)
	{
		sec = ((1.0-(float)soc/100) *(float)BATTERY_CAPACITY_MWH/1000 * 3600) / power;
		hours = sec / 3600;
		minutes = sec % 3600 / 60;
	}
	else
	{
		hours = 0;
		minutes = 0;
	}

}
static void calculate_average_power(void)
{
	// applying Incremental (Rolling) Average Method
	average_power = average_power + (power - average_power)/++number_of_power_sample;
}


static void calculate_total_energy_charged(void)
{
	total_energy_charged += power * TIME_INTERVAL;
}
static void track_maximum_voltage_current_temperature(void)
{
	if (voltage>max.voltage)
	{
		max.voltage = voltage;
	}
	if (current>max.current)
	{
		max.current = current;
	}
	if (temperature>max.temperature)
	{
		max.temperature = temperature;
	}
}
void detect_overvoltage(void)
{
	if (voltage > MAXIMUM_VOLTAGE)
	{
		fault_detected = 1;
	}
}
void detect_undervoltage(void)
{
	if (voltage < MINIMUM_VOLTAGE)
	{
		fault_detected = 1;
	}
}
void detect_overcurrent(void)
{
	if (current>MAXIMUM_CHARGE_CURRENT)
	{
		fault_detected = 1;
	}
}
void detect_short_circuit(void)
{
	if (voltage < SHORT_CIRCUIT_VOLTAGE_THRESHOLD && current>SHORT_CIRCUIT_CURRENT_THRESHOLD)
	{
		fault_detected = 1;
	}
}
