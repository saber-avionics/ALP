#ifndef _AIRTEMP_H
#define _AIRTEMP_H

int32_t adcInit(void);
float getVoltage(int32_t adcReading);
float getTemperature(void);

#endif // !_AIRTEMP_H
