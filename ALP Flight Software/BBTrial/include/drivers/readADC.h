#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

int readAnalog(int number);
