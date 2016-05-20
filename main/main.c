/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0b00001111;
	PORTA = 0b11111111;
    while (1) 
    {
		
    }
}

