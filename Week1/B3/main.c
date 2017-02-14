/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	blinking LEDS in PORTD between Pin 7 and Pin 6, ony if PORTC pin 0 is pressed
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
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b11111110; 			// All pins PORTC are set to output, except pin 0

	while (1)
	{
		if(PINC & 1) 			// If Pin 0 (0b00000001) is pressed

		{
			PORTD = 0b10000000;		// PortD: Pin 7 of set to on, rest off
			wait( 500 );			// Wait 0,5 sec
			PORTD = 0b00000000;		// PortD: all pins are off
			wait( 500 );			// Wait 0,5 sec
		}

	}

}
