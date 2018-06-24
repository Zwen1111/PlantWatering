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

	static MoistureSensor& getInst() {
		static MoistureSensor instance;
		return instance;
	}

	int getValue();
	void setPin(int pin) {
		this->pin = pin;
		pinMode(pin, INPUT);
	}

	int pin;
};

#endif

