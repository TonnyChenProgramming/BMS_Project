#ifndef __CALCULATIONS_H
#define __CALCULATIONS_H

#include "main.h"

typedef struct {
	int hours;
	int minutes;
	int secs;
} Time_t;

typedef struct{
	float power;
	BatteryStatus batteryStatus;
	int hours;
	int minutes;
} Process_Data_t;

extern Process_Data_t process_data;


void processing(void);


#endif
