#include "drivers/XA1110.h"

using namespace std;

bool XA1110::begin(uint8_t I2CBus, uint8_t I2CAddress) {
	I2CDevice(I2CBus, I2CAddress);
	//this->I2CAddress = I2CAddress;
	//this->I2CBus = I2CBus;
}