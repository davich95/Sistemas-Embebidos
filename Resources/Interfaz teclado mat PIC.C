/**
 * Procesa las entradas del teclado matricial y determina la tecla que esta
 * siendo oprimida. Retorna una palabra binaria de 16 bits en la cual los bits
 * que se encuentran en estado alto representan teclas oprimidas.
 *
 * Esta función esta diseñada para poder detectar cuando se oprimen varias
 * teclas sin embargo, debido a limitantes de la forma de conexión del teclado
 * matricial, no se deben esperar resultados correctos al oprimir varias teclas
 *
 * @return Retorna una palabra de 16 bits, cada bit representa una tecla.
 */
uint16_t keypad_read()
{
	unsigned char count = 0;
	unsigned char bitmask = 0x10;
	
	// Valor de retorno de la funcion keypad_read() entero de 16 bits
	uint16_t keys =0;

	// Revisamos si alguna de las lineas en la parte baja esta en estado alto
	// debido a que se ha cerrado un switch en el teclado.
	if( PORTB & 0x0F )
	{
		// Escaneamos las filas una por una para determinar la tecla oprimida
		do
		{
			// Apagamos todas las filas (parte alta)
			PORTB &= 0x0F;
			// Seleccionamos solo una como salida (bit del registro tris = 0)
			TRISB &= ~bitmask;
			// Y colocamos el pin en estado alto
			PORTB |= bitmask;
			// Esperamos unos cuantos milisegundos y leemos las columnas
			delay_ms(100);
			// Guardamos las columnas en una variable de 16 bits
			keys |= (PORTB & 0x0F);
			// Si ya hemos leido 4 columnas, las siguientes instrucciones no son
			// necesarias, por lo que salimos del ciclo
			if( count == 3 )
				break;
			// Recorremos la lectura a la izquierda para hacer espacio
			keys = keys<<4;
			// Recorremos el bitmask de la fila a leer
			bitmask = bitmask<<1;
			// Incrementar el contador de filas
			count ++;
		} while(1);

		// Mantenemos parte alta = salidas y parte baja = entradas
		TRISB = 0x0F;
		// Mantenemos los bits mas significativos del puerto en estado alto
		PORTB = 0xF0;
		return keys;
	}
	return 0;
}