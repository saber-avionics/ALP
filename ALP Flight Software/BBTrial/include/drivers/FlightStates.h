#ifndef _FLIGHTSTATES_H
#define _FLIGHTSTATES_H

#include <stdint.h>
#include <iostream>

enum flightState { UNARMED, STANDBY, ASCENT, FLOATING, DESCENT, LANDING };
flightState myFS = UNARMED;

class States {
public:
	//void whichState(flightState newState);
	void unarmed();
	void standby(float smoothAltitude, float initialAltitude);
	void ascent(float velocity);
	void floating(float velocity);
	bool descent(float velocity, float gForce, bool parachuteDeployed, float altitude);
	void landing();
};


#endif // !_FLIGHTSTATES_H