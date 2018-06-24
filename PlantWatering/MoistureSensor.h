// MoistureSensor.h

#ifndef _MOISTURESENSOR_h
#define _MOISTURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MoistureSensor {
public:
	MoistureSensor();
	MoistureSensor(int pin);

	int getValue();

	int pin;
};

#endif

