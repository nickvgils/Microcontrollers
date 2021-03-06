/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	ISR functions who are calling each other (without using the while loop )
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

	// Init ISR
	ISR( INT0_vect ) 	// called when input 0 changes
	{
		wait(3000); 	// wait 3 sec
		PORTD = 0b00000010; // turn on pin 1 (LED)
	}

	ISR( INT1_vect ) // called when input 1 changes
	{
		wait(3000); 	// wait 3 sec
		PORTD = 0b00000100; // turn on pin 2 (LED)
	}

	ISR( INT2_vect ) // called when input 2 changes
	{
		wait(3000); // wait 3 sec
		PORTD = 0b00000001; // turn on pin 0 (LED)
	}


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	
	// Init I/O
	DDRD = 0b11111111;			// PORTD(0:7) output

	// Init Interrupt hardware
	EICRA |= 0b00111111;			// INT2, INT1, INT0 rising edge
	EIMSK |= 0b00000111;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
	PORTD = 0b00000001; // pin 0 triggers a rising edge

	while (1)
	{
		wait( 10000 ); // waits infinity for 1 sec, does nothing in the while loop
	}

	return 1;

}
