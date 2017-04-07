/*
 * LCD.c
 *
 * Created: 16/02/2017 11:55:39
 *  Author: Timon
 */ 

 #include "lcd.h"
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>

 void lcd_command(unsigned char dat)
 {
	PORTC = dat & 0xF0;     //0b1111 0000
	PORTC = PORTC | 0x08;   //0b0000 1000

	_delay_ms( 1 );
	PORTC = 0x00;          //0b0000 0100

	PORTC = (dat & 0x0F) << 4;    //0b0000 1111
	PORTC = PORTC | 0x08;         //0b0000 1000

	_delay_ms(1);
	PORTC = 0x00;
 }

  void lcd_writeChar(unsigned char dat)
  {
	  PORTC = dat & 0xF0;
	  PORTC = PORTC | 0x0C;

	  _delay_ms( 1 );
	  PORTC = 0x00;

	  PORTC = (dat & 0x0F) << 4;
	  PORTC = PORTC | 0x0C;

	  _delay_ms(1);
	  PORTC = 0x00;
  }

  void lcd_writeLine(char* ptrArray)
  {
	lcd_command(0x02);
	int index = 0;
	while(ptrArray[index] != '\0')
	{
		lcd_writeChar(ptrArray[index]);
		index++;
	}
  }

 void lcd_init(void)
 {
	//These steps are always neccesary for the lcd to start

	//return home
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x80);
 }

 void lcd_clear(void)
 {
	lcd_writeLine("                ");

 }

 void lcd_set_cursor()
 {
	lcd_command(0x18);
 }