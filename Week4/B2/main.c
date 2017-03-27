#define  F_CPU 8000000

#include "lcd.h"

void wait( int );
/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	displays the output of an adc converter on the leds
					conversion on request
					
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			nick.vangils@hotmail.com
** -------------------------------------------------------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BIT(x)	(1 << (x))



/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	
	// Init I/O
	
	DDRF = 0x00; //ADC pin on input
	DDRA = 0xFF; //PIN A leds on output
	DDRB = 0xFF;
	
	ADMUX = 0b01100011; 
	ADCSRA = 0b10000110;
	// input 3: PF3
	// single ended
	// prescaler = 64 (fosc = 8MHz à 125 kHz <200 kHz)
	// conversion on request
	// no interrupt
	// 10 bits, left positioned
	// Vref = 5V (intern Vcc)
			
	
	while (1)
	{
		
		ADCSRA |= BIT(6);				// Start ADC
		while ( ADCSRA & BIT(6) ) ;		// Wait for completion
		PORTB ^= 0x01;
		PORTA = ADCH;					// Show MSB (bit 9:2) of ADC
		wait(500);			//wait 0,5 sec for a new conversion
			
	}

	return 1;


}