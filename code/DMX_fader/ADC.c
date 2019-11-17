/*
 * ADC.c
 *
 * Created: 12.10.2013 18:27:59
 *  Author: Ole
 */ 

#include "ADC.h"
#include "DMX_transmit.h"
#include "TWI_slave.h"
#include <avr/interrupt.h>

#define BUT0_LED PC0
#define BUT1_LED PD2
#define BUT2_LED PD4

#define BUT0 PB2
#define BUT1 PD0
#define BUT2 PD3

volatile uint8_t counter = 1;

void leds_and_buttons_init()
{
	//leds
	DDRC |= (1<<BUT0_LED);
	DDRD |= (1<<BUT1_LED) | (1<<BUT2_LED);
	
	PORTC &= ~(1<<BUT0_LED);
	PORTD &= ~((1<<BUT1_LED) | (1<<BUT2_LED));
	//PORTC |= (1<<BUT0_LED);
	//PORTD |= (1<<BUT1_LED) | (1<<BUT2_LED);
	
	//buttons
	DDRD &= ~((1<<BUT1) | (1<<BUT2));
	DDRB &= ~(1<<BUT0);
	//pullup
	PORTD |= (1<<BUT1) | (1<<BUT2);
	PORTB |= (1<<BUT0);
}

void adc_init()
{
	DDRC &= ~((1<<PC1) | (1<<PC2) | (1<<PC3));
	//PORTC |= (1<<PC1) | (1<<PC2) | (1<<PC3);
	//ADC1, AREF, left adjust 
	ADMUX = counter | (1<<ADLAR);		
	//enable, start conversion, interrupt enable, XTAL divide by 128 => 16Mhz/128 = 125 KHz
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
																						
	sei();
}


ISR(ADC_vect)
{
	DmxField[counter - 1] = ADCH;
	
	if (PINB & (1<<BUT0))
	{
		PORTC |= (1<<BUT0_LED);
		DmxField[0] = 255;
	}
	else
	{
		PORTC &= ~(1<<BUT0_LED);
	}
	
	if (PIND & (1<<BUT1))
	{
		PORTD |= (1<<BUT1_LED);
		DmxField[1] = 255;
	}
	else
	{
		PORTD &= ~(1<<BUT1_LED);
	}
	
	if (PIND & (1<<BUT2))
	{
		PORTD |= (1<<BUT2_LED);
		DmxField[2] = 255;
	} 
	else
	{
		PORTD &= ~(1<<BUT2_LED);
	}
	
	/*
	uint8_t adc_value = ADCH;
	
	if (counter == 1)
	{
		if (adc_value > 127)
		{
			PORTC |= (1<<BUT0_LED);
		}
		else
		{
			PORTC &= ~(1<<BUT0_LED);
		}
	}
	if (counter == 2)
	{
		if (adc_value > 127)
		{
			PORTD |= (1<<BUT1_LED);
		}
		else
		{
			PORTD &= ~(1<<BUT1_LED);
		}
	}
	if (counter == 3)
	{
		if (adc_value > 127)
		{
			PORTD |= (1<<BUT2_LED);
		}
		else
		{
			PORTD &= ~(1<<BUT2_LED);
		}
	}
	*/
	
	counter++;
	
	if (counter > 3)
	{
		counter = 1;
		//TWI_update_buffer(DmxField, DMX_LENGTH);
	}
	//choose next channel
	ADMUX = counter | (1<<ADLAR);
	
	//start new conversion
	ADCSRA |= (1<<ADSC);
}