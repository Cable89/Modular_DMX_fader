/*
 * HysteresisFilter.h
 *
 * Created: 17/09/2020 18:35:28
 *  Author: Oystein
 */ 


#ifndef HYSTERESISFILTER_H_
#define HYSTERESISFILTER_H_

#include <avr/io.h>

#define HYSTERESIS_BITS 2
#define HYSTERESIS_OFFSET 0
#define HYSTERESIS_MARGIN ( (1UL << HYSTERESIS_BITS) - 1 )
#define HYSTERESIS_MAX_IN (1UL << 10)
#define HYSTERESIS_MAX_OUT (HYSTERESIS_MAX_IN >> HYSTERESIS_BITS)

uint8_t hysteresisfilter(uint16_t in, uint8_t prevlevel);

#endif /* HYSTERESISFILTER_H_ */