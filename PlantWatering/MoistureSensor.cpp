// 
// 
// 

#include "MoistureSensor.h"

MoistureSensor::MoistureSensor() {

}

MoistureSensor::MoistureSensor(int pin) {
	this->pin = pin;
	pinMode(pin, INPUT);
}

int MoistureSensor::getValue() {
	return analogRead(this->pin);
}
