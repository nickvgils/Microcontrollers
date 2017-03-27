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
** Beschrijving:	displays the output of an adc converter on a LCD where a thermometer is connected on PF3
					
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
	DDRC = 0xFF;
	
	ADMUX = 0b11100011; 
	ADCSRA = 0b11100110;
	// input 3: PF3, thermometer on this pin
	// single ended
	// prescaler = 64 (fosc = 8MHz à 125 kHz <200 kHz)
	// free running mode
	// no interrupt
	// 10 bits, left positioned
	// Vref = 2,5V (intern Vcc)
			
	lcd_init();
	
	while (1)
	{
		
	PORTB = ADCL; //low register output of the adc converter shown at B leds
	PORTA = ADCH; //high register output of the adc converter shown at A leds
	
	char str[15];
	
	sprintf(str, "%d graden", ADCH);
	
	lcd_writeLine(str);		// show the high register output on the lcd
	wait(300);
	lcd_clear();
	}

	return 1;


}