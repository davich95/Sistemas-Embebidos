/*
 * practica1.c
 *
 * Created: 19/5/2016 10:11:35
 * Author : David- Hugo- Paul
 * LAS TABULACIONES SON CON 4 ESPACIOS
 */
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
//Version Jefferson
/*
int aux=0;
int cont=0;
int unidad, decena, centena, mil;
int numeros[10] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000011, 0b1111000, 0b0000000, 0b0011000};

ISR(INT0_vect){
	aux=2;
}

ISR(INT1_vect){
	aux=1;
}

ISR(INT2_vect){
	cont=0;
	aux=1;
}


int mostrar(int numero)
{
	mil=numero/1000;
	centena=numero/100;
	decena=numero/10;
	unidad=numero%10;
	if(numero>=100 && numero<1000)
	{
		decena=decena%10;
	}
	if (numero>=1000)
	{
		decena=decena%100;
		decena=decena%10;
		centena=centena%10;
	}
	for (int i=0;i<5;i++)
	{
		PORTA=0x80;
		PORTC=numeros[unidad];
		_delay_ms(100);
		
		PORTA=0x40;
		PORTC=numeros[decena];
		_delay_ms(100);
		
		PORTA=0x20;
		PORTC=numeros[centena];
		_delay_ms(100);
		
		PORTA=0x10;
		PORTC=numeros[mil];
		_delay_ms(1100);
		
	}
	
	return 0;
}

int main(void)
{
	DDRC=0xff;
	DDRA=0xf0;
	PORTA=0x0f;
	
	//GICR=0b01000000;//habilitar interrupcion externa 0
	GICR=0b11100000;//habilitar interrupcion externa 0 1 2
	MCUCR=0b01001111;//configurar deteccion de interrupcion
	sei();//activador global de interrupciones
	aux=1;
	while(1){
		mostrar(cont);
		if (cont ==0){
			aux=1;
		}
		if(aux==1){
			cont++;
			}else{
			cont--;
		}
		if (cont > 9999){
			cont=0;
		}
	}
}
*/
//Version inicial
/*
#define F_CPU  8000000UL
#include <avr/io.h>
#include <avr/interrupt.h> //Librería para interrupciones
#include <util/delay.h>
//Variables Globales
int count[10] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000011, 0b1111000, 0b0000000, 0b0011000};
//Fin Variables  
ISR(INT0_vect)
{

}
int main(void)
{
	sei();
	int A = 0b00010000;
    DDRC = 0b1111111;
	DDRD = 0b11110000;
	GICR = 0b11000000;
	MCUCR = 0b0001010;
    while(1)
    {		

		for(int i = 1;i<=4;i++)
		{
			PORTD = A;
			A =  A << 1;
			_delay_ms(500);
		}
		A = 0b00010000;
    }
}
*/
int count[10] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000011, 0b1111000, 0b0000000, 0b0011000};
int main(void)
{
	sei();
	GICR = 0b11100000;
	MCUCR = 0b00001111;
	MCUCSR = 0b01000000;
	DDRC = 0b11111111;
	while(1)
	{
		
	}
}