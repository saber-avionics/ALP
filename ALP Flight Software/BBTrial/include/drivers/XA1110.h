#pragma once

#include <stdint.h>
#include <string>
#include "drivers/I2CDevice.h"

using namespace std;

#define MT333x_ADDR 0x10 //7-bit unshifted default I2C Address

#define MAX_PACKET_SIZE 255
//If packet size is ever more than 255 the head and tail variables will need to be
//changed to something other than uint8_t

#define I2C_SPEED_STANDARD        100000
#define I2C_SPEED_FAST            400000

class XA1110 {
public:
	bool begin(uint8_t I2CBus, uint8_t I2CAddress);
	
};