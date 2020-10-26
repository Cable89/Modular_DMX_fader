/*
 * DMX_fader.c
 *
 * Created: 28.02.2015 13:01:18
 *  Author: Ole
 */ 

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "general.h"
#include "DMX_transmit.h"
#include "ADC.h"

#ifdef SLAVE
#include "TWI_slave.h"
#endif

#ifdef MASTER
#include "TWI_Master.h"
#endif



int main(void)
{
 	
	//calibrate frequency
	//OSCCAL = 0xC6;
	
	// Own TWI slave address
	#ifdef SLAVE
		//unsigned char TWI_slaveAddress = 0x10;
		unsigned char TWI_slaveAddress = ( ( ~((ADDRESS_PORT & ADDRESS_MASK) >> ADDRESS_OFFSET) + 1) << 1);
	
		unsigned char msgLength = 4;
		volatile unsigned char msg[4] = {0, 0, 0, 0};

		// Initialise TWI module for slave operation. Include address and/or enable General Call.
		TWI_Slave_Initialise( (unsigned char)((TWI_slaveAddress<<TWI_ADR_BITS) ));
		TWI_Start_Transceiver_With_Data(msg, msgLength);
	#endif
	#ifdef MASTER
		TWI_Master_Initialise();
		
		
		
		msg[0] = (TWI_slaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT);
		msg[1] = 0xAA;
		TWI_Start_Read_Write(msg, msgLength);
		
		init_dmx();
	#endif
	
	leds_and_buttons_init();
	adc_init();
	
	sei();
	
    while(1)
    {	
		
    }
}


