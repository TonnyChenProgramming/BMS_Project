#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include "main.h"  // Always include main.h for HAL libraries

// Function prototypes
void oled_init(void);
void oled_display(float voltage,float current, int soc, float power,float temperature,int soh,
		char* status, int hours, int minutes);

#endif /* OLED_DISPLAY_H */
