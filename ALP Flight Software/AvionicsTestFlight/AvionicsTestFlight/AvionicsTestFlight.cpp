// AvionicsTestFlight.cpp : This file contains the 'main' function. Program execution begins and ends there.

// main file for the SABER ALP Avionics

//#include "stdafx.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <cctype>

#include "FlightStates.h"
#include "vn/sensors.h"
#include "vn/thread.h"
#include "vn/compositedata.h"

using namespace std;
using namespace vn::math;
using namespace vn::sensors;
using namespace vn::protocol::uart;
using namespace vn::xplat;



extern float initialAltitude;
extern flightState myFS;

float temperature;
float pressure;
uint32_t initialPressure;

//void executeCommands();
double getAltitude(double initialPressure, double currentPressure);

int main()
{
	//--Initialize Variables
	cout << "Beginning ALP Software" << endl;
	uint16_t packetCount = 0;
	struct timespec timevar;
	double startTime = 0;
	double missionTime = 0;
	bool parachuteDeployed = false;
	//float batteryTemp = tempC.readTempC();
	pressure = 0;//getPressure();
	initialPressure = 0;
	float initialAltitude = 0;
	float baroAltitude = 0;
	double gpsAltitude = 0;
	float velocity = 0;
	double smoothing_factor = 0.90;
	float smoothAltitude = 0;
	float smoothAGL = 0;
	float smoothVelocity = 0;
	float gForce = 0;
	vec3f orientation;
	vec3f acceleration;
	//const string sensorPort = "COM1";				// Windows USB Port
	//const string sensorPort = "/dev/ttyS1";		// Linux Physical Serial Port
	const string sensorPort = "/dev/ttyUSB0";		// Linux USB Port
	const uint32_t sensorBaudrate = 115200;
	myFS = UNARMED;



	//--Initialize Classes
	cout << "Initializing Classes" << endl;
	//MCP9808 tempC;
	States states;
	//Mechanical mech; used globally, not needed here
	VnSensor vs;
	CompositeData cd;



	//--Initialize Sensors
	cout << "Initializing Sensors" << endl;
	//tempC.begin();
	//altCal(pressure, airTemp);
	vs.connect(sensorPort, sensorBaudrate);
	string modelNumber = vs.readModelNumber();
	cout << "Model Number: " << modelNumber << endl;

	//--Testing VectorNav
	vec3f ypr = vs.readYawPitchRoll();
	cout << "Current YPR: " << ypr << endl;
	YawPitchRollMagneticAccelerationAndAngularRatesRegister reg;
	reg = vs.readYawPitchRollMagneticAccelerationAndAngularRates();
	cout << "Current YPR: " << reg.yawPitchRoll << endl;
	cout << "Current Magnetic: " << reg.mag << endl;
	cout << "Current Acceleration: " << reg.accel << endl;
	cout << "Current Angular Rates: " << reg.gyro << endl;
	float presTest = vs.readImuMeasurements().pressure;
	cout << "Pressure: " << presTest << endl;		//doesn't work yet

//--Initializing Start Data
	startTime = clock_gettime(CLOCK_MONOTONIC, &timevar);
	initialAltitude = getAltitude(101.325, vs.readImuMeasurements().pressure);

//--Main Loop--------------------------------------------------------------------------------------
	while (1) {
		//executeCommands();
		packetCount++;
		missionTime = clock_gettime(CLOCK_MONOTONIC, &timevar);
		//------Sensor Measurements
		pressure = vs.readImuMeasurements().pressure;
		temperature = vs.readImuMeasurements().temp;
		//batteryTemp = tempC.readTempC();
		//airTemp = getTemperature();
		//baroAltitude = getBaroAltitude(pressure, airTemp);
		smoothAltitude = smoothing_factor * getAltitude(101.325, pressure) + (1 - smoothing_factor)*smoothAltitude;
		smoothAGL = smoothAltitude - initialAltitude;
		//velocity = getVelocity(baroAltitude);
		smoothVelocity = smoothing_factor * velocity + (1 - smoothing_factor)*smoothVelocity;
		orientation = vs.readYawPitchRoll();
		acceleration = vs.readImuMeasurements().accel;
		usleep(1000000);

		//Output
		string packet = "";
		packet += "UAH SABER Avionics Flight Test";
		packet += ",";
		packet += to_string(packetCount);
		packet += ",";
		packet += to_string(missionTime);
		packet += ",";
		packet += to_string(myFS);
		packet += ",";
		packet += to_string(temperature);
		packet += ",";
		packet += to_string(pressure);
		packet += ",";
		packet += to_string(smoothAGL);
		packet += ",";
		packet += to_string(orientation.x) + "," + to_string(orientation.y) + "," + to_string(orientation.z);
		packet += ",";
		packet += to_string(acceleration.x) + "," + to_string(acceleration.y) + "," + to_string(acceleration.z);
		cout << packet << endl;

//------Flight States

		switch (myFS) {
		case UNARMED:
			//Just chillin'.
			//cout << "UNARMED" << endl;
			states.unarmed();
			break;
		case STANDBY:
			//I'M READY!!!
			//cout << "STANDBY" << endl;
			states.standby(smoothAltitude, initialAltitude);
			break;
		case ASCENT:
			//Here we go!
			//cout << "ASCENT" << endl;
			states.ascent(smoothVelocity, baroAltitude, initialAltitude);
			break;
		case FLOATING:
			//I can see my house from here.
			//cout << "FLOATING" << endl;
			states.floating(smoothVelocity);
			break;
		case DESCENT:
			//Down, down, down...
			//cout << "DESCENT" << endl;
			parachuteDeployed = states.descent(smoothVelocity, gForce, parachuteDeployed, smoothAltitude);
			break;
		case LANDING:
			//Getting kinda lonely, someone come find me.
			//cout << "LANDING" << endl;
			states.landing();
			break;
		}

	}

	return 0;
}

/*
void executeCommands() {
	string myCommand = getCommand();
	cout << "Command Recieved: " << myCommand << endl;
	if (myCommand == "ARM") {
		mech.arm(); //I don't think this will ever do anything...
		myFS = STANDBY;
	}
	else if (myCommand == "ABORT") {
		mech.abort();
	}
	else if (myCommand == "LAUNCH") {
		bool weAreGoForLaunch = true;
		mech.launch(weAreGoForLaunch);
	}
	else if (myCommand == "IMUCAL") {
		mech.IMUcal();
	}
	else if (myCommand == "ALTCAL") {
		altCal(pressure, airTemp);
	}
	else if (myCommand == "SOFTRESET") {
		mech.SoftReset();
	}
	else if (myCommand == "HARDRESET") {
		mech.HardReset();
	}
	else if (myCommand == "CAMERAON") {
		mech.CameraOn();
	}
	else if (myCommand == "CAMERAOFF") {
		mech.CameraOff();
	}
	else if (myCommand == "TAKEPICTURE") {
		mech.TakePicture();
	}
	else if (myCommand == "BUZZERON") {
		mech.BuzzerOn();
	}
	else if (myCommand == "BUZZEROFF") {
		mech.BuzzerOff();
	}
	else if (myCommand == "SETSTATE") {
		cout << "Which State?";
		string stateCommand;
		cin >> stateCommand;
		if (stateCommand == "UNARMED") {
			myFS = UNARMED;
		}
		else if (stateCommand == "STANDBY") {
			myFS = STANDBY;
		}
		else if (stateCommand == "ASCENT") {
			myFS = ASCENT;
		}
		else if (stateCommand == "FLOATING") {
			myFS = FLOATING;
		}
		else if (stateCommand == "DESCENT") {
			myFS = DESCENT;
		}
		else if (stateCommand == "LANDING") {
			myFS = LANDING;
		}
		else {
			cout << "Not a valid Flight State." << endl;
		}
	}
	else {
		cout << "Not a valid command" << endl;
	}
	
}*/


double getAltitude(double initialPressure, double currentPressure) {
	return 44330.0*(1 - pow((currentPressure / initialPressure), (1 / 5.255)));
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
