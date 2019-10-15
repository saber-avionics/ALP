// main.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <cctype>

#include "drivers\AirTemp.h"
#include "drivers\altitude.h"
#include "drivers\BatteryTemp.h"
#include "drivers\FlightStates.h"
#include "drivers\Mechanical.h"
#include "drivers\UART.h"
#include "vn/sensors.h"
#include "vn/thread.h"

using namespace std;
using namespace vn::math;
using namespace vn::sensors;
using namespace vn::protocol::uart;
using namespace vn::xplat;

Mechanical mech;

void main()
{
//--Initialize Variables
	
	bool parachuteDeployed = false;
	//float batteryTemp = tempC.readTempC();
	float airTemp = getTemperature();
	uint32_t pressure = 0;
	uint32_t initialPressure = 0;
	float initialAltitude = getAltitude(initialPressure, pressure, airTemp);
	float altitude = 0;
	float velocity = 0;
	double smoothing_factor = 0.50;
	float smoothAltitude = 0;
	float smoothVelocity = 0;
	float gForce = 0;
	const string sensorPort = "COM1";				// Windows USB Port
	//const string SensorPort = "/dev/ttyS1";		// Linux Physical Serial Port
	//const string SensorPort = "/dev/ttyUSB0";		// Linux USB Port
	const uint32_t sensorBaudrate = 115200;
	
	

//--Initialize Classes
	//MCP9808 tempC;
	States states;
	//Mechanical mech; used globally, not needed here
	VnSensor vs;



//--Initialize Sensors
	//tempC.begin();
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



//--Main Loop--------------------------------------------------------------------------------------
	while (1) {
		executeCommands();
//------Sensor Measurements
		pressure = 0;
		//batteryTemp = tempC.readTempC();
		airTemp = getTemperature();
		altitude = getAltitude(initialPressure, pressure, airTemp);
		smoothAltitude = (smoothing_factor * altitude + (1 - smoothing_factor)*smoothAltitude);
		velocity = getVelocity(altitude);
		smoothVelocity = (smoothing_factor * velocity + (1 - smoothing_factor)*smoothVelocity);
		cout << "hello there" << endl;
		//delay(1000);

//------Flight States
		
		switch (myFS) {
		case UNARMED:
			//Just chillin'.
			cout << "UNARMED" << endl;
			states.unarmed();
			break;
		case STANDBY:
			//I'M READY!!!
			cout << "STANDBY" << endl;
			states.standby(smoothAltitude, initialAltitude);
			break;
		case ASCENT:
			//Here we go!
			cout << "ASCENT" << endl;
			states.ascent(smoothVelocity);
			break;
		case FLOATING:
			//I can see my house from here.
			cout << "FLOATING" << endl;
			states.floating(smoothVelocity);
			break;
		case DESCENT:
			//Down, down, down...
			cout << "DESCENT" << endl;
			parachuteDeployed = states.descent(smoothVelocity, gForce, parachuteDeployed, smoothAltitude);
			break;
		case LANDING:
			//Getting kinda lonely, someone come find me.
			cout << "LANDING" << endl;
			states.landing();
			break;
		}
				
	}
	
}

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
		altCal();
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

}
