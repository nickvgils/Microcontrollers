/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0b10000001, 2000}, {0b01000010, 2000}, {0b00100100, 2000}, {0b00011000, 2000}
};


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

ISR( INT0_vect )
{
	wait(3000);
	PORTD = 0b00000010;
}

ISR( INT1_vect )
{
	wait(3000);
	PORTD = 0b00000100;
}

ISR( INT2_vect )
{
	wait(3000);
	PORTD = 0b00000001;
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
	EICRA |= 0b00111111;			// INT2 rising edge, INT1 rising edge, INT0 rising edge
	EIMSK |= 0b00000111;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
	PORTD = 0b00000001;

	while (1)
	{
		wait( 500 );
	}

	return 1;


}
