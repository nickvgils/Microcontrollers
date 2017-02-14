/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	LED pattern made by a lookup table as a struct
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

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; // A struct has been defined as an binary data element and a preferred // delay. Saved as PATTERN_STRUCT

PATTERN_STRUCT pattern[] = {
	{0b10000001, 2000}, {0b01000010, 2000}, {0b00100100, 2000}, {0b00011000, 2000}
};	// A new PATTERN_STRUCT has been made with a pattern of different binaries.



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
	DDRD = 0b11111111; // All pins PORTD are set to output


	int index = 0; // Counter

	while (1)
	{
		if(index > 4) // If the counter has reached the last element
		{
			index = 0; // index back to zero to display the first element
		}

		// Write data to PORTD
		PORTD = pattern[index].data; // portD is set to the data field of the // pattern index
		wait(pattern[index].delay); // Wait is set to the delay field of the // pattern index
	
		index++;	// increment for next round
	}



}
