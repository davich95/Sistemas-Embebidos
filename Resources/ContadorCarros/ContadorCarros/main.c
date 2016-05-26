/*
 * ContadorCarros.c
 *
 * Created: 25/5/2016 23:11:44
 * Author : David
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int decodificador[10] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000011, 0b1111000, 0b0000000, 0b0011000};
int valor = 0; int cont = 1;
ISR(INT0_vect) //Incrementa
{
	if ((valor == 200) && (cont == 1))
	{
		valor = 200; cont = 0;
	}
	if ((valor == 0) && cont == 0)
	{
		 cont = 1;
	}
	valor=valor + cont;
}
ISR(INT1_vect) //Decrementa
{
	if ((valor == 0) && cont == 1)
	{
		valor = 0; cont = 0;
	}
	if ((valor == 200) &&  (cont == 0))
	{
		valor = 200; cont = 1;
	}
	valor=valor - cont;
}
int display (int numero)
{
	for (int i = 0; i<=2; i++)
	{
		PORTA = 0b00000001;
		PORTC = decodificador[numero%10]; //Unidades
		_delay_ms(50);
		PORTA = 0b00000010;
		PORTC = decodificador[(numero/10)%10]; //Decenas
		_delay_ms(50);
		PORTA = 0b00000100;
		PORTC = decodificador[(numero/100)%10]; //Centenas
		_delay_ms(50);
	}
	return 0;
}
int main(void)
{
	sei(); //habilitador de interrupciones
	DDRC = 0b1111111;
	DDRA = 0b00011111;
	DDRB = 0b00000011;
	GICR = 0b11000000; //Interrupciones  0 y 1
	MCUCR = 0b00001111; //flanco de subida
	//int valor = 0; int cont = 1;
    while (1) 
    {
		display(valor);
		if (valor < 200)
		{
			PORTB = 0b00000010;
		} 
		else
		{
			PORTB = 0b00000001;
		}
    }
}