#ifndef BUZZER_H
#define BUZZER_H

#include "main.h"  // Always include main.h for HAL libraries

#define buzzer_on() do{HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);}while(0);
#define buzzer_off() do{HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);}while(0);

// Function prototypes
void buzzer_init(void);
#endif
