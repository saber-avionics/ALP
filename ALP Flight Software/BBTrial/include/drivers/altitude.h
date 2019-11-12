#pragma once

#include <stdint.h>

#ifndef ALTITUDE_H_
#define ALTITUDE_H_

float getBaroAltitude(uint32_t pressure, float temperature);

void altCal(uint32_t pressure, float temperature);

float getVelocity(float altitude);

#endif  /*ALTITUDE_H_*/