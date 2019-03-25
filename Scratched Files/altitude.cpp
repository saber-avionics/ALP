#include "c:\program files (x86)\atmel\studio\7.0\toolchain\avr8\avr8-gnu-toolchain\avr\include\stdint.h"
#include "altitude.h"
#include "pressure.h"
#include "temperature.h"
#include "stdafx.h"
#include <math.h>
#include <iostream>

//uint32_t getAltitude(uint32_t initial, uint32_t pressure);

uint32_t getAltitude(uint32_t initial, uint32_t pressure) {
	//printf("Initial Pressure = %lu\n", initial);
	//printf("pressure = %lu \n", pressure);
	//printf("temperature = %li \n", TEMP/100);
	//float altitude = (((287.058 * (((float)(TEMP)/100)+273.15)/9.8))*log((float)initial/get_pressure())*3.28);	Not this one, this one's bad
	//float altitude = (pow(((initial/100)/(pressure/100)),(1/5.257))-1)*((TEMP/100)+273.15)/.0065; //This is now right, just gotta use the thermistor
	uint32_t altitude = ((float)initial - (float)pressure) / (1.225f * 9.81f);
	//printf("altitude = %f \n", (float)altitude);
	return altitude;
}

/*uint32_t getVelocity(uint32_t altitude) {
	uint32_t velocity = 
	return velocity;
}*/