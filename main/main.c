/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David Aguilar - Hugo Rengifo - Paul Armijos
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"
int keypad  (void)
{ int a;
	PORTB=1;
		a=PINB&0b11110000;
		a=a>>4;
		if(a==1) return '7';//-7-	
		if(a==2) return '8';//-8-
		if(a==4) return '9';//-8-
		if(a==8) return 'C';//-/-
	PORTB=2;
		a=PINB&0b11110000;
		a=a>>4;
		if(a==1) return '4';//-4-
		if(a==2) return '5';//-5-
		if(a==4) return '6';//-6-
		if(a==8) return 'B';//*
	PORTB=4;
		a=PINB&0b11110000;
		a=a>>4;
		if(a==1) return '1';//-1-
		if(a==2) return '2';//-2-``
		if(a==4) return '3';//-3-
		if(a==8) return 'A';
	PORTB=8;
		a=PINB&0b11110000;
		a=a>>4;
		if(a==1) return '#';//-on/c-
		if(a==2) return '0';//-0-
		if(a==4) return '*';//-=-
		if(a==8) return 'D';//+
	_delay_ms(50);
	return 20;	
}
int main(void)
{
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	while(1)
	{
		lcd_clrscr();
		lcd_puts("Ingrese dato");
		_delay_ms(200);
	}
}