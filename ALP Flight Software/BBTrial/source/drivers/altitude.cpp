#include <stdint.h>
#include "drivers/altitude.h"
#include "drivers/pressure.h"
#include "drivers/AirTemp.h"
//#include "stdafx.h"
#include <iostream>
#include <math.h>

//uint32_t getAltitude(uint32_t initial, uint32_t pressure);

float getAltitude(uint32_t initial, uint32_t pressure, float temperature) {
	//printf("Initial Pressure = %lu\n", initial);
	//printf("pressure = %lu \n", pressure);
	//printf("temperature = %li \n", TEMP/100);
	//float altitude = (((287.058 * (((float)(TEMP)/100)+273.15)/9.8))*log((float)initial/get_pressure())*3.28);	Not this one, this one's bad
	float altitude = (pow(((initial/100)/(pressure/100)),(1/5.257))-1)*((temperature/100)+273.15)/.0065; //This is now right, just gotta use the thermistor
	//uint32_t altitude = ((float)initial - (float)pressure) / (1.225f * 9.81f);
	//printf("altitude = %f \n", (float)altitude);
	return altitude;
}

void altCal() {
	//Calibrate the Altitude
}

float getVelocity(float altitude) {
	float velocity = 0;
	return velocity;
}