#ifndef __CALCULATIONS_H
#define __CALCULATIONS_H

#include "main.h"

typedef struct {
	int hours;
	int minutes;
	int secs;
} Time_t;

extern Time_t time_pack;

extern float power;
void processing(void);


#endif
