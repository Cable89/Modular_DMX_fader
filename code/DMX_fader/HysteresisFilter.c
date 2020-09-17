/*
 * HysteresisFilter.c
 *
 * Created: 17/09/2020 18:35:17
 *  Author: Oystein
 */ 
#include "HysteresisFilter.h"

uint8_t hysteresisfilter(uint16_t in, uint8_t prevlevel){
	uint16_t prevLevelFull = (prevlevel << HYSTERESIS_BITS) | HYSTERESIS_OFFSET;
	uint16_t lowerbound = prevlevel > 0 ? prevLevelFull - HYSTERESIS_MARGIN : 0;
	uint16_t upperbound = prevlevel < HYSTERESIS_MAX_OUT ? prevLevelFull + HYSTERESIS_MARGIN : HYSTERESIS_MAX_IN;
	if(in < lowerbound || in > upperbound){
		//*prevlevel = in >> HYSTERESIS_BITS;
		return in >> HYSTERESIS_BITS;
	}
	return prevlevel;
}