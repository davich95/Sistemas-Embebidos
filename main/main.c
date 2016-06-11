/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David Aguilar - Hugo Rengifo - Paul Armijos
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
{ int a;
		a=PINB&0b11110000;
		a=a>>4;
		a=PINB&0b11110000;
		a=a>>4;
		a=PINB&0b11110000;
		a=a>>4;
		a=PINB&0b11110000;
		a=a>>4;
	_delay_ms(50);
	return 20;	
}
int main(void)
{
	while(1)
	{
		_delay_ms(200);
	}
}