#include "constants.h"
#include "calculations.h"
#include "sensing.h"
float power = 0;
int soc = 0;
int soh = 0;
int hours = 0;
int minutes = 0;

// Declare functions
static int calculate_soc(void);
static int calculate_soh(void);
static inline float calculate_power(void);
static void calculate_remaining_time(void);
void calculate_oled_parameters(void);
float calculate_total_energy_charged(void);

void calculate_oled_parameters(void)
{
	// oled requires voltage, current, soc, power, temperature, soh, status, hours, minutes
	soc = calculate_soc();
	soh = calculate_soh();
	power = calculate_power();
	calculate_remaining_time();
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
	return;
}
float calculate_total_energy_charged(void)
{
    // Use the inline function to calculate power
    //float power = calculate_power(voltage, current);
    // Calculate energy charged in watt-hours (Wh)
    //float energy_charged = power * (time_interval / 3600.0); // Convert seconds to hours
    //return energy_charged;
	return 0.0;
}


