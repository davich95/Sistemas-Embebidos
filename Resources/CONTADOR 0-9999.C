#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int aux=0;
int cont=0;
int unidad, decena, centena, mil;
int numeros[10]={64, 121, 36, 48, 25, 18, 3, 120, 0, 24};
	
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
		_delay_ms(5);
		
		PORTA=0x40;
		PORTC=numeros[decena];
		_delay_ms(5);
		
		PORTA=0x20;
		PORTC=numeros[centena];
		_delay_ms(5);
		
		PORTA=0x10;
		PORTC=numeros[mil];
		_delay_ms(5);
		
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
