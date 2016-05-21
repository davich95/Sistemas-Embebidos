#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int sig=1;
int ayu=-1;
int help=-1;
int aux=0;
int contador=0;

int millares,centenas,decenas,unidades,i;
int matriz[10]={64, 121, 36, 48, 25, 18, 3, 120, 0, 24};

int mostrar(int numeros)
	{
		millares=numeros/1000;
		centenas=numeros/100;
		decenas=numeros/10;
		unidades=numeros%10;
		if(numeros>=100 && numeros<1000)
		{
			decenas=decenas%10;
		}
		if (numeros>=1000)
		{
			decenas=decenas%100;
			decenas=decenas%10;
			centenas=centenas%10;
		}
		for (i=0;i<5;i++)
		{
			PORTD=0x80;
			PORTC=matriz[unidades];
			_delay_ms(5);
			
			PORTD=0x40;
			PORTC=matriz[decenas];
			_delay_ms(5);
			
			PORTD=0x20;
			PORTC=matriz[centenas];
			_delay_ms(5);
			
			PORTD=0x10;
			PORTC=matriz[millares];
			_delay_ms(5);
			
		}
			
		return 0;
	}
int segundos(int seg)
	{
		seg++;
		_delay_ms(100);
		return(seg);
	}

	
int main(void)
{	
	DDRC=0xff;
	DDRD=0xf0;
	DDRB=0xf0;
	PORTB=0x0f;
	PORTD=0x0f;

	while (1) 
    {
	
			if ((PIND&(1<<0))==1 && ayu==-1)
			{
				sig=sig*ayu;
				ayu=1;
				help=-1;
			}
			if ((PIND&(1<<1))==2 && ayu==1)
			{
				sig=sig*help;
				ayu=-1;
				help=1;
			}
			if ((PIND&(1<<2))==4)
			{
				if(ayu==1)
				{
					contador=9999;
					sig=-1;
					}else{
					contador=0;
					sig=1;
				}
			}
			aux=contador;
			if (contador<0)
			{
				aux=aux*(-1);
			}
			mostrar(aux);
			contador=contador+sig;
			if (contador>9999)
			{
				contador=0;
			}
			if (contador<0 && sig==-1)
			{
				contador=9999;
			}
		}
}
