/*
 * DMX_transmit.c
 *
 * Created: 28.02.2015 16:43:35
 *  Author: Ole
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define USART_BAUDRATE 250000
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define IBG (10)
#define F_OSC (16000)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "DMX_transmit.h"

// ********************* local definitions *********************
volatile uint16_t 		gCurDmxCh;		//current DMX channel
volatile uint8_t		gDmxState;

enum {BREAK, STARTB, DATA};

void init_dmx()
{
	UCSR0B = (1 << TXEN0) | (1 << TXCIE0); // Turn on the transmission circuitry, transmit complete interrupt
	UCSR0C =  (3 << UCSZ00 ) | (1 << USBS0 ); // Use 8- bit character sizes - URSEL bit set to select the UCRSC register 2 stop bits
	UBRR0H = ( BAUD_PRESCALE >> 8); // Load upper 8- bits of the baud rate value into the high byte of the UBRR register
	UBRR0L = BAUD_PRESCALE ; // Load lower 8- bits of the baud rate value into the low byte of the UBRR register
	UDR0    = 0;							//start USART

	//fill array with zeros
	for (int i = 0; i < DMX_LENGTH; i++)
	{
		DmxField[i] = 0;
	}
	
	//Data
	gDmxState= BREAK;					//start with break
}

ISR(USART_TX_vect)
{
	uint8_t DmxState= gDmxState;

	if (DmxState == BREAK)
	{
		UBRR0H  = 0;
		UBRR0L  = (F_OSC/1600);					//90.9kbaud with 8MHz clock
		UDR0    = 0;								//send break ( ca 121 us)
		gDmxState= STARTB;
	}
	else if (DmxState == STARTB)
	{
		UBRR0H  = 0;
		UBRR0L  = ((F_OSC/4000)-1);				//250kbaud
		UDR0    = 0;								//send start byte
		gDmxState= DATA;
		gCurDmxCh= 0;
		//no need to wait for MAB, long enough from just executing code
	}
	else
	{
		//_delay_us(IBG);
		uint16_t CurDmxCh= gCurDmxCh;
		UDR0 = DmxField[CurDmxCh++];				//send data
		if (CurDmxCh == DMX_LENGTH) 
			gDmxState= BREAK; //new break if all ch sent
		else 
			gCurDmxCh= CurDmxCh;
	}
}