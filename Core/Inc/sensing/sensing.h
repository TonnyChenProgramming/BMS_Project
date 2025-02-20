#ifndef SENSING
#define SENSING

#include "main.h"  // Always include main.h for HAL libraries
#include "stdint.h"

extern float voltage;
extern float current;
extern float temperature;
extern uint32_t dma_adc_buffer[10];
extern char* status;
// Function prototypes
void reconfigure_to_dual_mode(void);
void reconfigure_to_temperature_channel(void);
void read_temperature(void);
void process_voltage_and_current_data(void);


#endif /* OLED_DISPLAY_H */
