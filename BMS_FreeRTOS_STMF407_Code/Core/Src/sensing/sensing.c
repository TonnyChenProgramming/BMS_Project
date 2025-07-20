#include "main.h"
#include "math.h"

#define VREF_ACTUAL1 2.94  // Measured VDD
#define VREF_ACTUAL2 5.2

// current sensing constants
#define ZERO_CURRENT_OFFSET 2.52
#define SENSITIVITY ((0.185/5)*VREF_ACTUAL2)

//temperature sensing constants
#define UPPER_RESISTANCE 10000
#define BETA_NTC 4100
#define ROOM_TEMPERATURE 298.15

uint32_t dma_adc_buffer[10] ={0,0,0,0,0,0,0,0,0,0};
uint32_t adc_voltage_raw_sum = 0;
uint32_t adc_current_raw_sum = 0;
uint32_t adc_voltage_raw = 0;
uint32_t adc_current_raw = 0;
uint32_t adc_temperature_raw = 0;
float voltage = 0.0; // store voltage in mV
float current = 0.0; // store current in mA
float temperature = 0.0;



void reconfigure_to_dual_mode(void);
void reconfigure_to_temperature_channel(void);
void read_temperature(void);
static inline float convert_adc_raw_voltage_in_mV(uint32_t adc_voltage_raw);
static inline float convert_adc_raw_current_in_mA(uint32_t adc_current_raw);
static inline float convert_adc_raw_temperature(uint32_t adc_temperature_raw);
void process_voltage_and_current_data(void);

void reconfigure_to_dual_mode(void)
{
	HAL_ADC_DeInit(&hadc1);  // Fully reset ADC1
	MX_ADC1_Init();
    //restart dual mode
	HAL_TIM_Base_Start(&htim2);
    HAL_ADC_Start(&hadc2);
    HAL_ADC_Start_DMA(&hadc1, dma_adc_buffer, 8);
}


void reconfigure_to_temperature_channel(void)
{
	// stop dual mode
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_ADC_Stop(&hadc2);

	//switch ADC1 to independent mode

	HAL_ADC_DeInit(&hadc1);  // Fully reset ADC1

	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    HAL_ADC_Init(&hadc1);

    ADC_MultiModeTypeDef multimode = {0};
    multimode.Mode = ADC_MODE_INDEPENDENT;
    if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
    {
        Error_Handler();
    }

    // Switch ADC1 to PA3 (Temperature)
    ADC_ChannelConfTypeDef sConfig1 = {0}; // Use a local struct
    sConfig1.Channel = ADC_CHANNEL_3;
    sConfig1.Rank = 1;
    sConfig1.SamplingTime = ADC_SAMPLETIME_56CYCLES;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig1) != HAL_OK)
    {
      Error_Handler();
    }

}


void read_temperature(void)
{
   adc_temperature_raw = 0;  // Reset previous readings

   // Start ADC Conversion
   // ✅ Start ADC Conversion (Software Trigger)
   HAL_ADC_Start(&hadc1);

   // Wait for ADC conversion to complete
   HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

   // Read ADC value
   adc_temperature_raw = HAL_ADC_GetValue(&hadc1);

   // Stop ADC after reading
   HAL_ADC_Stop(&hadc1);

   //get the temperature value
   temperature = convert_adc_raw_temperature(adc_temperature_raw);
}
static inline float convert_adc_raw_voltage_in_mV(uint32_t adc_voltage_raw) {
    return (((float)adc_voltage_raw * VREF_ACTUAL1) / 4095.0 * 1.5 * 1000);
}


static inline float convert_adc_raw_current_in_mA(uint32_t adc_current_raw) {
    float Vout = ((float)adc_current_raw * VREF_ACTUAL1) / 4095.0;
    return (Vout - ZERO_CURRENT_OFFSET) / SENSITIVITY * 1000;  // ✅ Only returns the result, no side effects
}

static inline float convert_adc_raw_temperature(uint32_t adc_temperature_raw) {
    float Vntc = ((float)adc_temperature_raw * VREF_ACTUAL1) / 4095.0;
    float Rntc = (Vntc * UPPER_RESISTANCE) / (VREF_ACTUAL1 - Vntc);

    return (1.0f / ((log(Rntc / UPPER_RESISTANCE) / BETA_NTC) + (1.0f / ROOM_TEMPERATURE))) - 273.15f;
}

void process_voltage_and_current_data(void)
{
	adc_voltage_raw_sum = 0;
	adc_current_raw_sum = 0;
	//collect voltage and current raw data, add them to sum for averaging

	for (int counter = 0;counter<8;counter++)
	{
		adc_voltage_raw_sum += (dma_adc_buffer[counter] & 0xFFFF);
		adc_current_raw_sum += (dma_adc_buffer[counter] >> 16);
	}

	adc_voltage_raw = adc_voltage_raw_sum / 8;
	adc_current_raw = adc_current_raw_sum / 8;
	voltage = convert_adc_raw_voltage_in_mV(adc_voltage_raw);
	current = convert_adc_raw_current_in_mA(adc_current_raw);
	// the current should never less than zero, if it does, just set it to 0
	if (current <0)
	{
		current = 0.0;
	}

}
