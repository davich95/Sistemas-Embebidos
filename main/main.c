/*
 * main.c
 *
 * Created: 14/5/2016 18:33:15
 * Author : David Aguilar - Hugo Rengifo - Paul Armijos
 */ 
#include <avr/io.h>
#define F_CPU 8000000UL
#define USART_BAUDRATE 19200 //bps -- ingresar baud rate
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define ADC_VREF_TYPE 0x00
#include <util/delay.h>
#include <time.h>
#include "lcd.h"


int uart_putc(unsigned char c)
{
	while(!(UCSRA & (1 << UDRE))) /* wait, to UDR ready */
	{
	}
	UDR = c; /* send to indications */
	return 0;
}
void uart_puts (char *s)
{
	while (*s)
	{ /* so long *s! = ?\ 0? thus unequally the ?stringer end-character?*/
		uart_putc(*s);
		s++;
	}
}
unsigned int read_adc(unsigned char adc_input)
{
	ADMUX=adc_input;
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=0x40;
	// Wait for the AD conversion to complete
	while ((ADCSRA & 0x10)==0);
	ADCSRA|=0x10;
	return ADCW;
}
char send_key(void)
{
	char a;
	char vector;
	for (int i = 0; i < 4; i++)
	{
		a = '0'+ rand() % 9;
		UDR = a;
		vector = vector + a;
		_delay_ms(200);
	}
	_delay_ms(200);
	return vector;
}
void set_uart (void)
{
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
	UCSRA = 0b00000000; UCSRB = 0b00011000; UCSRC = 0b10000110; //Activar el bit 7 del UCSRB para interrupcion por RX completa
}

void configuraciones (void)
{
	DDRB=0b00001111;//TECLADO
	DDRC=0b11111111;//Pines indicadores del estado de la cerradura
	PORTD=0x00;  
	lcd_init (LCD_DISP_ON_CURSOR_BLINK); //Enciende el Lcd , enciende el cursor para poder escribir
}
int teclado (void)
{
	PORTB = 1;
	if (PINB & 1<<PINB4) return '^';//arriba
	if (PINB & 1<<PINB5) return '4';//4
	if (PINB & 1<<PINB6) return '7';//7
	if (PINB & 1<<PINB7) return '#';//#
	
	PORTB = 2;
	if (PINB & 1<<PINB4) return '1';//1
	if (PINB & 1<<PINB5) return '5';//5
	if (PINB & 1<<PINB6) return '8';//8
	if (PINB & 1<<PINB7) return '0';//0
	
	PORTB = 4;
	if (PINB & 1<<PINB4) return '2';//2
	if (PINB & 1<<PINB5) return '6';//6
	if (PINB & 1<<PINB6) return '9';//9
	if (PINB & 1<<PINB7) return '*';//*
	
	PORTB = 8;
	if (PINB & 1<<PINB4) return '3';//3
	if (PINB & 1<<PINB5) return '>';//>
	if (PINB & 1<<PINB6) return '<';//<
	if (PINB & 1<<PINB7) return 'M';//M
	
	_delay_ms(80);
	
	return 20;
}
int main(void)
{
	ADMUX=ADC_VREF_TYPE & 0xff;
	ADCSRA=0x83;
	set_uart();
	char caracter = '*';
	char passvalidar,a,tecla,pass;
	int contador=0;	
	int aux=0;
	int autorizacion=0;
	int cambio=0;
	//char str_temp[5];
	//int adc_data;
	//float temp;
	passvalidar=0;
	pass='0'+'1'+'2'+'3';
	
	configuraciones();
	lcd_puts("Bienvenido!");
	_delay_ms(1000);
	lcd_clrscr();
	lcd_puts("Presione M para");
	lcd_gotoxy(0,1);
	lcd_puts("obtener una key.");
	_delay_ms(2000);
	lcd_clrscr();
	srand(read_adc(7));
	while(1)
	{
// 		adc_data = read_adc(7);
// 		temp =adc_data*0.0049*100;
// 		lcd_clrscr();
// 		dtostrf(temp, 8, 4, str_temp);
// 		lcd_puts(str_temp);
		tecla=teclado();	
		if (tecla!=20)
		{
				lcd_putc(caracter);//el PUTC sirve para mostrar lo que se escribe en el  LCD
				a=tecla;
				contador=contador+1;
				passvalidar=passvalidar+a;
				if (tecla=='<')  // cuando presionamos flecha izquierda se borra lo escrito
				{
					lcd_clrscr(); // CLR scr  para limpiar el LCD (dejarlo en blanco)
					passvalidar=0;
					contador=0;
				}
				if (tecla=='M') // si presionamos  M cambiaremos la clave
				{
					lcd_clrscr();
					lcd_puts("Espere mientras");
					lcd_gotoxy(0,1);
					lcd_puts("la key se envia.");
					_delay_ms(2000);
					lcd_clrscr();
					cambio=1;
					contador=0;
					passvalidar=0;
				}
				if (cambio==1)
				{
					lcd_clrscr();
					_delay_ms(200);
					lcd_clrscr();
					contador=0;
					passvalidar=0;
					autorizacion=autorizacion+1;
					lcd_clrscr();
				}
				if (cambio==1)
				{
					if (autorizacion==1)
					{
						pass = send_key();
						_delay_ms(2000);
						UDR = 0x0d;
						_delay_ms(500);
						lcd_clrscr();
						lcd_puts("Clave enviada");
						lcd_gotoxy(0,1);
						lcd_puts("con exito!");
						_delay_ms(3000);
						lcd_clrscr();
						lcd_puts("Ingrese la clave");
						lcd_gotoxy(0,1);
						_delay_ms(1000);
						cambio=0;
						contador=0;
						autorizacion=0;
						passvalidar=0;
					}
				}
				if (cambio==0)
				{
					if (contador==4)
					{
						if (passvalidar==pass)
						{
							lcd_clrscr();
							lcd_puts("Clave correcta");
							PORTC=0b00000001;
							_delay_ms(800);
							PORTC=0b00000000;
							lcd_clrscr();
							lcd_puts("Presione M para");
							lcd_gotoxy(0,1);
							lcd_puts("obtener una key.");
							passvalidar=0;
							contador=0;
							
						}
						else
						{
							lcd_clrscr();
							lcd_puts("Clave incorrecta");
							_delay_ms(2000);
							lcd_clrscr();
							lcd_puts("Presione M para");
							lcd_gotoxy(0,1);
							lcd_puts("obtener una key.");
							aux=aux+1;
							passvalidar=0;
						}
					}
			}
		} 
		_delay_ms(200);
	}
}