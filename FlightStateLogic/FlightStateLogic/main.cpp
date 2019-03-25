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

/*Old Atmel Code, not sure how much changes...
uint16_t C1; // Pressure sensitivity; SENS
uint16_t C2; // Pressure offset; OFF
uint16_t C3; // Temperature coefficient of pressure sensitivity; TCS
uint16_t C4; // Temperature coefficient of pressure offset; TCO
uint16_t C5; // Reference temperature; Tref
uint16_t C6; // Temperature coefficient of the pressure; TEMPSENS

void spi_init(void) {
PORTC.DIRSET = 0b10110000; //Open the output pins for the SPI
PORTC.DIRCLR = 0b01000000; //Open the input pins for the SPI
PORTC.OUT = 0b10110000;
SPIC.CTRL = 0b01010011;
PORTD.DIRSET = 0b00000010;
}

void spi_write(uint8_t command) {
SPIC.DATA = command;
while (!(SPIC.STATUS >> 7)); //waits until the status register changes
}

uint8_t spi_read(void) {
spi_write(0xFF); //writes a max byte
return SPIC.DATA; //gets the data and returns value
}

void ms5607init(void) {
pres_select(); // Turn on output pin for port 4.
spi_write(0x1E);
pres_deselect(); //reset command for the sensor; refer to datasheet for more.
delay_ms(10);



//Get the programmatical settings from the sensor for future calculations.
C1 = prom_read(0xA2);
C2 = prom_read(0xA4);
C3 = prom_read(0xA6);
C4 = prom_read(0xA8);
C5 = prom_read(0xAA);
C6 = prom_read(0xAC);
}



uint16_t prom_read(uint8_t command) { // reads the specified data value stored in the sensor.
uint16_t data;
pres_select();
spi_write(command);
data = ((uint16_t)spi_read()) << 8;
data += spi_read();
pres_deselect();
delay_ms(1);
return data;
}

uint32_t data_read(uint8_t command) {
uint32_t data;
pres_select();
spi_write(command);
pres_deselect();
delay_ms(10); //delay to wait for the data output
pres_select();
spi_write(0x00);
data = ((uint32_t)spi_read()) << 16; //gets the first 16 bits of the sensor reading, shunts it to the front of the integer.
data += ((uint32_t)spi_read()) << 8; // gets another 8 bits of the reading, shunts it in as well.
data += (uint32_t)spi_read(); // gets the final 8 bits from the sensor.
pres_deselect();
//delay_ms(10);
return data;
}

PressData get_pressure(void) { //refer to the datasheet for these calculations.

uint32_t D1 = data_read(0x48); // Gets digital pressure value
uint32_t D2 = data_read(0x58); // Gets temperature value

//

("D1: %lu, D2: %lu", D1, D2);

int32_t dT = (int64_t)D2 - (int64_t)C5 * 256; // Runs calculations to get dT
int32_t TEMP = 2000 + (int64_t)dT * (int64_t)C6 / 8388608; // Finds actual temp
//printf("TEMP: %li", TEMP);

int64_t OFF = (int64_t)C2 * 131072 + ((int64_t)C4 * (int64_t)dT) / 64;
int64_t SENS = (int64_t)C1 * 65536 + ((int64_t)C3 * (int64_t)dT) / 128;
int32_t P = ((int64_t)D1 * (int64_t)SENS / 2097152 - (int64_t)OFF) / 32768; // Gets the actual temperature and type casts it.
//printf("Test: %lld\n", test);
//int32_t P = 0;
PressData pd;
pd.TEMP = TEMP;
pd.P = P;
return pd;
}

void pres_select(void) {
PORTD_OUTCLR = 0b0000010;
}

void pres_deselect(void) {
PORTD_OUTSET = 0b00000010;
}
*/

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