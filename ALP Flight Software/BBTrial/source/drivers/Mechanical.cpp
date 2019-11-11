#include <iostream>
#include <stdint.h>
#include "drivers/Mechanical.h"

void Mechanical::arm() {
	//Arm the ALP
	//Does this even do anything?
}
void Mechanical::abort() {
	//Abort Rocket Launch
	OpenTrapDoor();
	//delay a bit
	OpenVent();
	ExplosiveSeparation();
	HotwireSeparation();
}
void Mechanical::launch(bool weAreGoForLaunch) {
	if (weAreGoForLaunch == true) {
		//Launch rocket
	}
}
void Mechanical::IMUcal() {
	//Calibrate the IMU
	//Doesn't belong here, just until I get the imu driver
}
void Mechanical::SoftReset() {
	//Soft Reset the BBG
}
void Mechanical::HardReset() {
	//Hard Reset the BBG
}
void Mechanical::CameraOn() {
	//Turn Camera On
}
void Mechanical::CameraOff() {
	//Turn Camera Off
}
void Mechanical::TakePicture() {
	//Take a Picture
}
void Mechanical::BuzzerOn() {
	//Turn Buzzer On
}
void Mechanical::BuzzerOff() {
	//Turn Buzzer Off
}
bool Mechanical::OpenTrapDoor() {
	//Open ALP Trap Door
	bool trapDoorOpened = true;
	return trapDoorOpened;
}
bool Mechanical::OpenVent() {
	//Open Balloon Vent
	bool ventOpened = true;
	return ventOpened;
}
bool Mechanical::ExplosiveSeparation() {
	//Activate Explosive Separation
	bool explosivelySeparated = true;
	return explosivelySeparated;
}
bool Mechanical::HotwireSeparation() {
	//Activate Hotwire Separation
	bool hotwireSeparated = true;
	return hotwireSeparated;
}
bool Mechanical::DeployParachute() {
	//Deploy the Parachute
	bool parachuteDeployed = true;
	return parachuteDeployed;
}