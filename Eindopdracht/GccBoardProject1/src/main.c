#define  F_CPU 8000000

#define BEGINSTATE 0
#define ANSWER 1
#define RESPONSE 2


void wait( int );
void beginState(void);
void exItrInit(void);
/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	blinking LEDS in PORTD between Pin 7 and Pin 6
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			nick.vangils@hotmail.com
** -------------------------------------------------------------------------*/

#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int state = BEGINSTATE;
int score = 0;
int numbers[50];
int currentPosition = 0;

void initBeginState(void)
{
	lcd_clear();
	lcd_writeLine("Druk op een knop");		// show the high register output on the lcd
}

void checkNumber(int buttonNumber)
{
	if(state == RESPONSE)
	{
		lcd_clear();
		if(numbers[currentPosition] == buttonNumber)
		{		
			if(currentPosition == score)
			{
					lcd_writeLine("goed gedaan!");
					score++;
					currentPosition = 0;
					wait(4000);
					state = ANSWER;
			}else{
					lcd_writeLine("goed, volgende?");
					currentPosition++;
			}
		}
		else{
			lcd_writeLine("fout");
			score = 0;
			currentPosition = 0;
			wait(4000);
			initBeginState();
			state = BEGINSTATE;
		}
	}
}

ISR( INT7_vect )
{
	checkNumber(3);
}
ISR( INT6_vect )
{
	checkNumber(2);
}
ISR( INT5_vect )
{
	checkNumber(1);
}
ISR( INT4_vect )
{
	checkNumber(0);
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

void beginState(void)
{
		if((PINA | PINB | PIND | PINF | PING) > 1)
		{
			state = ANSWER;
			srand(TCNT1);
		}
}

void exItrInit(void)
{
	EICRB |= 0xFF; // EX0, EX1: rising edge
	EIMSK |= 0xF0; // enable intrpt EX7, EX6, EX5, EX4
	sei();
}

void vulEnToonGetallen(void)
{
		lcd_writeLine("Onthoud de leds!");
		int i;
		for(i = 0 ; i < (score + 1) ; i++)
		{
			if(i == score)
				numbers[i] = rand() % 4;
				
			PORTE = (1 << 4) << numbers[i];
			//char letters[12];
			//sprintf(letters, "%d", numbers[i]);
			//lcd_writeLine(letters);
			wait(4000);
		}
		state = RESPONSE;
		PORTE = 0x00;
		
		lcd_clear();
		lcd_writeLine("Doe het na!");
		
		
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

	
	DDRA = 0x00;
	DDRB = 0x00;
	
	DDRC = 0xFF;
	lcd_init(); // initialize lcd
	
	DDRD = 0x00;
	
	DDRE = 0xFF; //input buttons, interrupt P4-P7
	
	DDRG = 0x00;
	DDRF = 0x00;
	

	TCCR1B |= 0b00000010;
	
	exItrInit();
		
	initBeginState();
	
	while (1)
	{
		
		switch(state)
		{
			case BEGINSTATE:
				beginState();
			break;
			case ANSWER:
				vulEnToonGetallen();
			break;
		}
		wait(100);
	}

	return 1;


}