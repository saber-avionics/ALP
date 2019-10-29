#include <stdint.h>
#include "drivers/altitude.h"
#include "drivers/pressure.h"
#include "drivers/AirTemp.h"
//#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

float initialAltitude;

float getAltitude(uint32_t pressure, float temperature) {
	uint32_t seaLevelPressure = 101325; //Pascals
	//printf("pressure = %lu \n", pressure);
	//printf("temperature = %li \n", TEMP/100);
	float altitude = (pow(((seaLevelPressure/100)/(pressure/100)),(1/5.257))-1)*((temperature/100)+273.15)/.0065; //Hypsometric formula, only good up to 11km
	//printf("altitude = %f \n", (float)altitude);
	return altitude;
}

//Calibrate the Altitude
void altCal(uint32_t pressure, float temperature) {
	float initAltArray[10] = {};
	float initAltTemp;
	float initAltSum = 0;
	for (uint8_t i = 0; i < 10;) {
		initAltTemp = getAltitude(pressure, temperature);
		if ((initAltTemp >= 0) && (initAltTemp <= 2000)) {
			initAltArray[i] = initAltTemp;
			initAltSum = initAltSum + initAltArray[i];
			i++;
		}
	}
	initialAltitude = initAltSum / 10;
	cout << "Initial Altitude: " << initialAltitude << endl;
	
}

float getVelocity(float altitude) {
	float velocity = 0;
	return velocity;
}