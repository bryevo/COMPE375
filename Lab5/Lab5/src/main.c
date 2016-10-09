#define FOSC 16000000 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <asf.h>

char scan_keypad();
void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char ch);

char scan_keypad()
{
	
	for (int col = 4; col < 8; col++)
	{
		PORTD |= 0xFF;		//reset
		PORTD &= ~(1<<col);		//sets specific PORTD/PIN(col) to 0 and everything else 1.
		for (int row = 0; row < 4; row++) 
		{
			PORTB |= 0x0F;		//reset
			if (!(PINB & (1<<row)) && !(PIND & (1<<col)))	//checks for 0's for the row and col
			{
				if (col == 4 && row == 0)
					return '1';
				else if (col == 4 && row == 1)
					return '2';
				else if (col == 4 && row == 2)
					return '3';
				else if (col == 4 && row == 3)
					return 'A';
				else if (col == 5 && row == 0)
					return '4';
				else if (col == 5 && row == 1)
					return '5';
				else if (col == 5 && row == 2)
					return '6';
				else if (col == 5 && row == 3)
					return 'B';
				else if (col == 6 && row == 0)
					return '7';
				else if (col == 6 && row == 1)
					return '8';
				else if (col == 6 && row == 2)
					return '9';
				else if (col == 6 && row == 3)
					return 'C';
				else if (col == 7 && row == 0)
					return '*';
				else if (col == 7 && row == 1)
					return '0';
				else if (col == 7 && row == 2)
					return '#';
				else if (col == 7 && row == 3)
					return 'D';
			}
		}	
	}
}

void USART_Init(unsigned int ubrr)
{
	/*baud rate*/
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	
	/*receiver and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/*frame format: 8data, 2stop bit*/
	UCSR0C = (3<<UCSZ00);
	
}
void USART_Transmit(unsigned char ch)
{
	
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	
	UDR0 = ch;          //This returns the char to the string
	
}
void main()
{
	DDRB |= 0x00;
	DDRD |= 0xF0;
	PORTB |= 0x0F;	//Low nibble
	PORTD |= 0xF0;	//High nibble
	char key;
	USART_Init(MYUBRR);
	while(1)
	{
		
		key = scan_keypad();
		USART_Transmit(key);
		_delay_ms(500);
	}

}