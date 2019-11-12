#ifndef _FLIGHTSTATES_H
#define _FLIGHTSTATES_H

#include <stdint.h>
#include <iostream>
#include <math.h>

enum flightState { UNARMED, STANDBY, ASCENT, FLOATING, DESCENT, LANDING };


class States {
public:
	//void whichState(flightState newState);
	void unarmed();
	void standby(float smoothAltitude, float initialAltitude);
	void ascent(float velocity, float smoothAltitude, float initialAltitude);
	void floating(float velocity);
	bool descent(float velocity, float gForce, bool parachuteDeployed, float altitude);
	void landing();
};


#endif // !_FLIGHTSTATES_H