/*
 * practica1.c
 *
 * Created: 23/5/2016 12:11:35
 * Author : David- Hugo- Paul
 */
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
int decodificador[10] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000011, 0b1111000, 0b0000000, 0b0011000};
int valor = 0;
int cont = 1;
ISR(INT0_vect) //Incremento	
{
	cont = 1;
}
ISR(INT1_vect) //Decremento
{
	cont = -1;
	
}
ISR(INT2_vect) //Reset
{
	valor = -1;
	cont = 1;
}
int display (int numero) 
{
	
	for (int i = 0; i<=1;i++)
	{
		PORTD = 0b00010000;
		PORTC = decodificador[numero%10]; //Se presentan las unidades
		_delay_ms(60);
		PORTD = 0b00100000;
		PORTC = decodificador[(numero/10)%10]; //Se presentan las decenas
		_delay_ms(60);
		PORTD = 0b01000000;
		PORTC = decodificador[(numero/100)%10]; //Se presentan las centenas
		_delay_ms(60);
		PORTD = 0b10000000;
		PORTC = decodificador[numero/1000]; //Se presentan los miles
		_delay_ms(60);
	}
	return 0;
}
int main(void)
{
	sei();
	GICR = 0b11100000; //Habilitar interrupciones 
	MCUCR = 0b00001111; //Detecta interrupciones por flanco de subida
	MCUCSR = 0b01000000;//Registro para detectar la interrupcion INT2
	DDRC = 0b11111111;
	DDRD = 0b11110000;
	cont = 1;
	while(1)
	{
		display(valor);			
		if ((valor==9999) && (cont == 1))	
		{
			valor = -1;
		}
		if ((valor == 0) && (cont == -1))
		{
			valor =9999;
		}
		valor = valor+cont;
	}
}