/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David Aguilar - Hugo Rengifo - Paul Armijos
 */ 
/*
 * LCD_TECLADO.c
 *
 * Created: 20/05/2016 17:20:47
 *  Author: Administrador
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
void configuraciones (void)
{
	DDRB=0b00001111;//TECLADO
	DDRD=0b11111111;//Pines indicadores del estado de la cerradura
	PORTD=0x00;  
	lcd_init (LCD_DISP_ON_CURSOR_BLINK); //Enciende el Lcd , enciende el cursor para poder escribir
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
	_delay_ms(50);
	return 20;	
}
int main(void)
{
	char j = '*';
	configuraciones();
	lcd_puts("INGRESE LA CLAVE");
	_delay_ms(1500);
	lcd_clrscr();
	while(1)
	{
		i = teclado();
	}
}

//Código anterior:
/*
int main(void)
{
	char j = '*';
	char pass;
	char b,a;
	int contador=0;
	int bloqueo=0;
	int autorizacion=0;
	int cambio=0;
	b=0;
	pass=0+'0'+'0'+'0'+'0'; //Pass por defecto
	char i;
	configuraciones();
	lcd_puts("INGRESE LA CLAVE");
	_delay_ms(1500);
	lcd_clrscr();
	while(1)
	{
		i=teclado();
		if (i!=20)
		{
			lcd_putc(i);//el PUTC sirve para mostrar lo que se escribe en el  LCD
			a=i;
			contador=contador+1;
			b=b+a;
			if (i=='<')  // cuando presionamos flecha izquierda se borra lo escrito
			{
				lcd_clrscr(); // CLR scr  para limpiar el LCD (dejarlo en blanco)
				b=0;
				contador=0;
			}
			if (i=='M') // si presionamos  M cambiaremos la clave
			{
				lcd_clrscr();
				lcd_puts("CAMBIO DE CLAVE");// PUT s para   mostrar en pantalla
				_delay_ms(2100);
				lcd_clrscr();
				lcd_puts("INSERTE CLAVE");
				lcd_gotoxy(0,1);
				lcd_puts("ANTERIOR");
				_delay_ms(2000);
				lcd_clrscr();
				cambio=1;
				contador=0;
				b=0;
			}
			if (cambio==1){
				if (contador==4){
					if (b==pass)
					{
						lcd_clrscr();
						lcd_puts("CORRECTO");
						_delay_ms(1000);
						lcd_clrscr();
						contador=0;
						b=0;
						autorizacion=autorizacion+1;
						lcd_puts("INSERTE NUEVA CLAVE");
						_delay_ms(1000);
						lcd_clrscr();
					}
				}
			}
			if (cambio==1){
				if (contador==4){
					if (autorizacion==1)
					{
						pass=b;
						lcd_clrscr();
						lcd_puts("CLAVE GUARDADA");
						_delay_ms(1000);
						lcd_clrscr();
						lcd_puts("INGRESE LA CLAVE");
						_delay_ms(1000);
						lcd_clrscr();
						cambio=0;
						contador=0;
						b=0;
					}
				}
			}
			if (cambio==0){
				if (contador==4){
					if (b==pass){
						lcd_clrscr();
						lcd_puts("CLAVE CORRECTA");
						PORTD=0b00000001;
						_delay_ms(2000);
						PORTD=0b00000000;
						lcd_clrscr();
						b=0;
						contador=0;
						}else{
						lcd_clrscr();
						lcd_puts("CLAVE INCORRECTA");
						PORTD=0b00000010;
						_delay_ms(2000);
						lcd_clrscr();
						bloqueo=bloqueo+1;
						if (bloqueo>=3)
						{
							lcd_clrscr();
							lcd_puts("EXCESO DE");
							lcd_gotoxy(0,1);
							lcd_puts("INTENTOS");
							PORTD=0x04;
							_delay_ms(3000);
							lcd_clrscr();
							lcd_puts("POR FAVOR CAMBIE");
							lcd_gotoxy(0,1);
							lcd_puts("DE CLAVE");
							_delay_ms(3300);
							lcd_clrscr();
							lcd_puts("PRESIONE M");
							_delay_ms(2000);
							}else{
							lcd_puts("INGRESE CLAVE");
							_delay_ms(2000);
							lcd_clrscr();
							PORTD=0x00;
							b='0';
							contador=0;
						}
					}
				}
			}
		}
		_delay_ms(200);
	}
}
*/