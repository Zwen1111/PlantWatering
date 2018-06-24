// 
// 
// 

#include "MoistureSensor.h"

MoistureSensor::MoistureSensor() {

}

int MoistureSensor::getValue() {
	return analogRead(this->pin);
}
