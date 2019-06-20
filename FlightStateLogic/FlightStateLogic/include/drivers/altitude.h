#pragma once

#include <stdint.h>

#ifndef ALTITUDE_H_
#define ALTITUDE_H_

uint32_t getAltitude(uint32_t initial, uint32_t pressure, int32_t temperature);

#endif  /*ALTITUDE_H_*/