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
	DDRC = 0b00001111; //Puerto C al teclado 4x4
    while (1) 
    {
		
    }
}

