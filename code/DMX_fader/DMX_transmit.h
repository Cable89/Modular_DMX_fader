/*
 * DMX_transmit.h
 *
 * Created: 28.02.2015 16:43:22
 *  Author: Ole
 */ 


#ifndef DMX_TRANSMIT_H_
#define DMX_TRANSMIT_H_

#include <avr/io.h>

#define DMX_LENGTH	50
volatile uint8_t	DmxField[DMX_LENGTH];		//array of DMX vals
void init_dmx();


#endif /* DMX_TRANSMIT_H_ */