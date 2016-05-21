//**************************************************************//
//System Clock                          :1MHz
//Software                                 :AVR Studio 4
//LCD Data Interfacing             :8-Bit
//**************************************************************//

#include<avr/io.h>
#define           F_CPU           1000000
#include<util/delay.h>
#define           KEYPAD_PORT           PORTC
/*Se define un macro para el archivo keypad.h KEYPAD_PORT es le puerto reguistrador del microcontrolador en el que  esta connectado el keypad 4x4. por default es el  PORTB*/

#define           KEYPAD_PIN           PINC
/*Se define un macro para el archivo keypad.h. KEYPAD_PIN es el PIN reguistrador del microcontrolador en el que  esta connectado el keypad 4x4. por default es el pin PINB*/

#include<avr/keypad.h>
/*Includes keypad.h header file which defines one function: read_keypad () to read the 4X4 keypad. Keypad header file version is 1.1*/

#define           LCD_DATA_PORT           PORTB
/*Defines a macro for the lcd.h header File. LCD_DATA_PORT is the microcontroller PORT Register to which the data pins of the LCD are connected. Default PORT Register for data pins in lcd.h header file is PORTA*/

#define           LCD_CONT_PORT           PORTD
/*Defines a macro for the lcd.h header File. LCD_CONT_PORT is the microcontroller PORT Register to which the control pins of the LCD are connected. Default PORT Register for control pins in lcd.h header file is PORTB*/

#define           LCD_RS           PD0
/*Defines a macro for the lcd.h header file. LCD_RS is the microcontroller Port pin to which the RS pin of the LCD is connected. Default Port pin for RS pin in lcd.h header file is PB0*/

#define           LCD_RW           PD1
/*Defines a macro for the lcd.h header file. LCD_RW is the microcontroller Port pin to which the RW pin of the LCD is connected. Default Port pin for RW pin in lcd.h header file is PB1*/

#define           LCD_EN           PD2
/*Defines a macro for the lcd.h header file. LCD_EN is the microcontroller Port pin to which the EN pin of the LCD is connected. Default Port pin for EN pin in lcd.h header file is PB2*/

#include<avr/lcd.h>
/*Includes lcd.h header file which defines different functions for all Alphanumeric LCD(8-Bit Interfacing Method). LCD header file version is 1.1*/

#include
/*Includes string.h header file which defines different string functions*/

int main(void)
{

	DDRB=0xff;
	/*All the 8 pins of PortB are declared output (data pins of LCD are connected)*/

	DDRD=0x07;
	/*PD0, PD1 and PD2 pins of PortD are declared output (control pins of LCD are connected)*/

	DDRC=0x0f;
	/*PortC’s upper 4 bits are declared input and lower 4 bits are declared output(4×4 Keypad is connected)*/

	PORTC=0xff;
	/*PortC’s lower 4 bits are given high value and pull-up are enabled for upper 4 bits*/

	unsigned char count=0, keypad_value, password_status=0;
	char password_set[5]="1234", password_entered[5];
	/*Variable declarations*/

	lcd_init();
	/*LCD initialization*/

	lcd_string_write("Bienvenido Amo");
	/*String display in 1st row of LCD*/

	lcd_command_write(0xc0);
	/*Cursor moves to 2nd row 1st column of LCD*/

	lcd_string_write("Entre y preparese para patear traceros con el  Davisho y el Hugo  :V plox");
	/*String display in 2nd row of LCD*/

	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	/*Display stays for 2 second*/

	lcd_command_write(0x01);
	/*Clear screen*/

	lcd_string_write("Enter Password");
	/*String display in 1st row of LCD*/

	/*While loop for password entry and checking*/
	while(password_status==0x00)
	{

		lcd_command_write(0xc0);
		/*Cursor moves to 2nd row 1st column of LCD*/

		/*While loop for 4 digit password entry*/
		while(count<4)
		{

			keypad_value=read_keypad();
			/*Scan’s 4X4 keypad and returns pressed key value or default value*/

			/*Checking if any key is pressed or not*/
			if(keypad_value != 0xff)
			{

				password_entered[count]=keypad_value+48;
				/*Storing the pressed key value of 4X4 keypad in ASCII format*/

				count++;
				/*Counter increment*/

				lcd_data_write(‘*’);
				/* Star(*) is displayed in 2nd row of LCD*/

			}
			else
			{

				;
				/*Null statement*/

			}

			_delay_ms(300);
			/*300ms delay as guard time between two consecutive pressing of key*/

		}

		count=0;
		/*Counter reset to 0*/

		password_entered[4]=0;
		/*Null character at the last of array(password_entered) to convert it to a string*/

		lcd_command_write(0x01);
		/*Clear screen*/

		/*Password Comparision*/
		if(!(strcmp(password_set,password_entered)))
		{

			lcd_string_write("Correct Password");
			/*String display in 1st row of LCD*/

			password_status=1;
			/*Changing the Password Status to Correct Password*/

		}
		else
		{

			lcd_string_write("Wrong Password");
			/*String display in 1st row of LCD*/

			_delay_ms(500);
			_delay_ms(500);
			_delay_ms(500);
			_delay_ms(500);
			/*Display stays for 2 second*/

			lcd_command_write(0x01);
			/*Clear screen*/

			lcd_string_write("Reenter Password");
			/*String display in 1st row of LCD*/

		}

	}

	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	/*Display stays for 2 second*/

	lcd_command_write(0x01);
	/*Clear Screen*/

	/*Start of infinite loop*/
	while(1)
	{

		lcd_command_write(0x80);
		/*Cursor moves to 2nd row 1st column of LCD*/

		lcd_string_write(“Press any Key”);
		/*String display in 1st row of LCD*/

		lcd_command_write(0xc0);
		/*Cursor moves to 2nd row 1st column of LCD*/

		lcd_string_write(“Key Value: “);
		/*String display in 1st row of LCD*/

		keypad_value=read_keypad();
		/*Scan’s 4X4 keypad and returns pressed key value or default value*/

		/*Checking if any key is pressed or not*/
		if(keypad_value!=0xff)
		{

			switch(keypad_value)
			{

				case 0:

				lcd_data_write("0");
				/*Displays 0 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 1:

				lcd_data_write("1");
				/*Displays 1 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 2:

				lcd_data_write("2");
				/*Displays 2 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 3:

				lcd_data_write("3");
				/*Displays 3 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 4:

				lcd_data_write("4");
				/*Displays 4 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 5:

				lcd_data_write("5");
				/*Displays 5 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 6:

				lcd_data_write("6");
				/*Displays 6 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 7:

				lcd_data_write("7");
				/*Displays 7 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 8:

				lcd_data_write("8");
				/*Displays 8 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 9:

				lcd_data_write("9");
				/*Displays 9 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 10:

				lcd_data_write("*")
				/*Displays * in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 11:

				lcd_data_write("#");
				/*Displays # in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 12:

				lcd_data_write("A");
				/*Displays A in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 13:

				lcd_data_write("B");
				/*Displays B in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 14:

				lcd_data_write("C");
				/*Displays C in 2nd row of LCD*/

				break;
				/*Break statement*/;

				case 15:

				lcd_data_write("D");
				/*Displays D in 2nd row of LCD*/

				break;
				/*Break statement*/;

			}

		}
		else
		{

			;
			/*Null statement*/

		}

		_delay_ms(300);
		/*300ms delay as guard time between two consecutive pressing of key*/

	}

}
