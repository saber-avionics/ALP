// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

unsigned int long getPressure();
unsigned int long getAltitude(unsigned int long initialPressure, unsigned int long pressure);
float getTemperature();
float getVectorNavData(void);

int main()
{
	int state = 0;
	unsigned int long pressure = 0;
	unsigned int long initialPressure = getPressure();
	unsigned int long altitude = 0;
	unsigned int long initialAltitude = getAltitude(initialPressure, pressure);
	float temperature = getTemperature();
	bool weAreGoForLaunch = false;
	float velocity = 0;
	double smoothing_factor = 0.50;
	unsigned int long smoothAltitude = 0;
	float G = 0;

	while (1) {
		pressure = getPressure();
		altitude = getAltitude(initialPressure, pressure);
		smoothAltitude = (smoothing_factor * altitude + (1 - smoothing_factor)*smoothAltitude);
		temperature = getTemperature();
		cout << "hello there" << endl;

		//delay(1000);

		if (state == 0) {
			//Perform Ground Operations
			if (smoothAltitude - initialAltitude >= 30) {
				cout << "Entering FS1" << endl;
				state = 1;
			}
		}
		if (state == 1) {
			//Perform Ascent Operations
			if (weAreGoForLaunch == true) {
				//Launch rocket
			}
			if (velocity <= -10) {
				cout << "Entering FS2" << endl;
				state = 2;
			}
		}
		if (state == 2) {
			//Perform Descent Operations
			//RLV Trap Door Open
			//Balloon Vent Open
			//Explosive Separation
			//Hotwire Separation
			//Deploy Parachute
			if (abs(velocity) <= 5 && G < .05) {
				cout << "Entering FS3" << endl;
				state = 3;
			}
		}
		if (state == 3) {
			//Perform Ground Operations
			//Run until powered off
		}
		
	}
	
	return 0;
}




unsigned int long getPressure(void) {
	//Do pressure stuff
	uint32_t pressure = 2;
	return pressure;
}

unsigned int long getAltitude(unsigned int long initialPressure, unsigned int long pressure) {
	//printf("Initial Pressure = %lu\n", initial);
	//printf("pressure = %lu \n", pressure);
	//printf("temperature = %li \n", TEMP/100);
	//float altitude = (((287.058 * (((float)(TEMP)/100)+273.15)/9.8))*log((float)initial/get_pressure())*3.28);	Not this one, this one's bad
	//float altitude = (pow(((initial/100)/(pressure/100)),(1/5.257))-1)*((TEMP/100)+273.15)/.0065; //This is now right, just gotta use the thermistor
	unsigned int long altitude = (unsigned int long)((float)initialPressure - (float)pressure) / (1.225f * 9.81f);
	//printf("altitude = %f \n", (float)altitude);
	return altitude;
}

float getTemperature(void) {
	float temperature = 26;
	return temperature;
}

float getVectorNavData(void) {
	float tiltx = 0;
	float tilty = 0;
	float tiltz = 0;
	float accelerationx = 0;
	float accelerationy = 0;
	float accelerationz = 0;
	float latitude = 0;
	float longitude = 0;
	return tiltx; return tilty; return tiltz;
	return accelerationx; return accelerationy; return accelerationz;
	return latitude; return longitude;
}