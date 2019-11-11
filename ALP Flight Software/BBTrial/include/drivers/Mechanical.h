#ifndef _MECHANICAL_H
#define _MECHANICAL_H

#include <iostream>
#include <stdint.h>

class Mechanical {
public:
	void arm();
	void abort();
	void launch(bool weAreGoForLaunch);
	void IMUcal();
	void SoftReset();
	void HardReset();
	void CameraOn();
	void CameraOff();
	void TakePicture();
	void BuzzerOn();
	void BuzzerOff();
	bool OpenTrapDoor();
	bool OpenVent();
	bool ExplosiveSeparation();
	bool HotwireSeparation();
	bool DeployParachute();
};

#endif // !_MECHANICAL_H

