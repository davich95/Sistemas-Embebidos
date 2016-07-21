/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David Aguilar - Hugo Rengifo - Paul Armijos
 */ 
#define F_CPU 8000000UL
#define USART_BAUDRATE 19200 //bps -- ingresar baud rate
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <util/delay.h>
#include <avr/io.h>
#include <time.h>
#include "lcd.h"

char vector[6];
void send_key(void)
{
	for (int i = 0; i < 6; i++)
	{
		vector[i] = '0'+ rand() % 9;
		_delay_ms(200);
	}
	for (int i = 0; i < 6; i++)
	{
		UDR = vector[i];
		_delay_ms(200);
	}
}
void setings (void)
{
	DDRB = 0b00001111;//TECLADO
	DDRC = 0b11111111;
	lcd_init (LCD_DISP_ON_CURSOR_BLINK); //Enciende el Lcd , enciende el cursor para poder escribir
}
void set_uart (void)
{
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRA = 0b00000000; UCSRB = 0b00011000; UCSRC = 0b10000110; //Activar el bit 7 del UCSRB para interrupcion por RX completa
}
int teclado  (void)
{ int a;
	PORTB=0b00000001;
	a=PINB&0b11110000;
	a=a>>4;
	if(a==0b00000001) return '1';//-*-
	if(a==0b00000010) return '2';//-#-
	if(a==0b00000100) return '3';//-^-
	if(a==0b00001000) return 'A';//->-
	PORTB=0b00000010;
	a=PINB&0b11110000;
	a=a>>4;
	if(a==0b00000001) return '4';//-1-
	if(a==0b00000010) return '5';//-4-
	if(a==0b00000100) return '6';//-7-
	if(a==0b00001000) return 'B';//0
	PORTB=0b00000100;
	a=PINB&0b11110000;
	a=a>>4;
	if(a==0b00000001) return '7';//-2-
	if(a==0b00000010) return '8';//-5-``
	if(a==0b00000100) return '9';//-8-
	if(a==0b00001000) return 'C';//M
	PORTB=0b00001000;
	a=PINB&0b11110000;
	a=a>>4;
	if(a==0b00000001) return '#';//3
	if(a==0b00000010) return '0';//6
	if(a==0b00000100) return '*';//9
	if(a==0b00001000) return 'D';//<
	_delay_ms(60);
	return 20;
}
int main(void)
{	
	setings();
	set_uart();
	
	char tecla;
	char passv[6];
	int i = 0;
	
	lcd_puts("Bienvenido!");
	_delay_ms(1000);
	lcd_clrscr();
	lcd_puts("Presione A para");
	lcd_gotoxy(0,1);
	lcd_puts("obtener una key.");
	_delay_ms(2000);
	lcd_clrscr();
	while(1)
	{
		
		tecla=teclado();
		if (tecla!=20)
		{
			if (tecla == 'A')
			{
				lcd_puts("Una key se envio");
				lcd_gotoxy(0,1);
				lcd_puts("a su email.");
				send_key();
				_delay_ms(2000);
				lcd_clrscr();
				lcd_puts("Ingrese la clave. ");
				lcd_gotoxy(0,1);
			}
			else
			{
				passv[i] = tecla;
				lcd_putc(passv[i]);
				_delay_ms(300);
				i++;
			}
			if (i >= 6)
			{
				int c = 0;
				for (int i = 0; i<6; i++)
				{
					if (passv[i] == vector[i])		//Compara si los vectores son iguales
					{
						c++;						//Por cada vez que una posicion del vector es igual con la del segundo vector, c se incrementa en 1 hasta llegar a 6
													//Si se ingresa un caracter que no coincida con el vector la variable c no va a incrementar y no va a llegar a 6
					}
				}
				if(c==6)							//Si toda la clave fue ingresada correctamente el contador c llegará a 6 y abrirá la cerradura
				{
					lcd_clrscr();
					lcd_puts("Clave correcta");
					PORTC = 0b00000001;
					_delay_ms(1000);
					PORTC = 0b00000000;
					lcd_clrscr();
					lcd_puts("Presione A para");
					lcd_gotoxy(0,1);
					lcd_puts("obtener una key.");
					_delay_ms(2000);
					lcd_clrscr();
				}
				else								//Si al menos 1 caracter ingresado es incorrecto, el contador no llegará a 6 y continuará a la siguiente seccion de código
				{
					lcd_clrscr();
					lcd_puts("Clave incorrecta");
					_delay_ms(1000);
					lcd_clrscr();
					lcd_puts("Presione A para");
					lcd_gotoxy(0,1);
					lcd_puts("obtener una key.");
					_delay_ms(2000);
					lcd_clrscr();
				}
				i = 0; //Reiniciar el iterador del vector
				c = 0; //Reiniciar el contador del vector
			}
		}
	}
}
