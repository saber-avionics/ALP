#pragma once

#include <stdint.h>

#ifndef ALTITUDE_H_
#define ALTITUDE_H_

float getAltitude(uint32_t initial, uint32_t pressure, float temperature);

void altCal();

float getVelocity(float altitude);

#endif  /*ALTITUDE_H_*/