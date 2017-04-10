#define F_CPU 8000000

#define BIT(x)	(1 << (x))

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

void wait(int);
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



ISR( TIMER2_COMP_vect )
{

	PORTD ^= BIT(7); // Toggle bit 0 van PORTC

	if(PORTD == 0){
		TCNT2 = 0;
		OCR2 = 195.3;
	}else{
		TCNT2 = 0;
		OCR2 = 117;
	}

}
	
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

void timer2Init( void )
{
	OCR2 = 117; // Compare value of counter 2
	TIMSK |= BIT(7); // T2 compare match interrupt enable
	SREG |= BIT(7); // turn_on intr all
	TCCR2 = 0b00001101; // Initialize T2: timer, prescaler=32,
	// compare output disconnected,CTC,RUN
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
	DDRD = 0xFF; // set PORTC for output (toggle PC0)
	PORTD = BIT(7);
	timer2Init();
	while (1)
	{
		// do something else
		wait(10); // every 10 ms (busy waiting
	}

}
