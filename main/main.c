/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David Aguilar - Hugo Rengifo - Paul Armijos
 */ 

#include <avr/io.h>


int main(void)
{
	// Ahora se está tratando de hacer la interfaz del teclado con el micro y el lcd
	DDRA = 0b00001111;
	PORTA = 0b11111111;
    while (1) 
    {
		
    }
}

