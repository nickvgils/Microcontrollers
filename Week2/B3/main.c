/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	Displays hexnumbers on PORTB on a 7 segment display
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


const unsigned char nummers[16] =
{
	0b00111111,		// 0
	0b00000110,		// 1
	0b01011011,		// 2
	0b01001111,		// 3
	0b01100110,		// 4
	0b01101101,		// 5
	0b01111101,		// 6
	0b00000111,		// 7
	0b01111111,		// 8
	0b01101111,	    // 9
	0b01110111,		// A
	0b01111111,		// B
	0b00001111,		// C
	0b01011110,		// D
	0b01111001,		// E
	0b01110001		// F	
};

void display(int digit){
	if(digit <= 15) // if digit below 16
	{
		DDRB = nummers[digit]; // digit is being displayed, number from lookup table
	}else{
		DDRB = nummers[14]; // else error sign(E), number from lookup table
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
	PORTB = 0b11111111;	// PORTB input
	PORTC = 0b00000000; // PORTC output
	int counter = 0;    // hexdecimal counter
	display(counter); //display a hex number, calles display method
	while(1)
	{
		if(PINC & 1) // if PORTC pin 0 (button) is pressed
		{
			counter++;
				display(counter);	// displays the counter
		}if(PINC == 0b00000010){	// if PORTC pin 1 (button) is pressed
			counter--;				// decrease the counter with 1
				display(counter);	// displays the counter
		}if(PINC == 0b00000011){	// if PORTC pin 0 and pin 1 (buttons) are pressed
				counter = 0;		// counter reset to 0
				display(counter);	// displays the 0
		}
		wait(1000); // waits for 1 sec
	
	}
}
