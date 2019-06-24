#pragma once

#ifndef PRESSURE_H_
#define PRESSURE_H_

/*
#include <asf.h>

typedef struct {
	int32_t TEMP;
	int32_t P;
} PressData;

/void spi_init(void);
void spi_write(uint8_t command);
uint8_t spi_read(void);
void ms5607init(void);
void pres_select(void);
void pres_deselect(void);
uint16_t prom_read(uint8_t command);
uint32_t data_read(uint8_t command);
PressData get_pressure(void);
int32_t TEMP;
*/

uint32_t getPressure(void);


#endif /* PRESSURE_H_ */