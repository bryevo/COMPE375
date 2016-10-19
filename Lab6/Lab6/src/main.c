#include <avr/io.h>
#include <util/delay.h>
#include <asf.h>

#define NOTE_ON PORTB |= (1<<PORTB5);
#define NOTE_OFF PORTB &= ~(1<<PORTB5);	

void scan_keypad();

void main()
{
	DDRB |= 0x00;
	DDRB |= (1<<DDB5);
	DDRD |= 0xF0;
	PORTB |= 0x0F;	//Low nibble
	PORTD |= 0xF0;	//High nibble
	while(1)
	{
		scan_keypad();
	}

}

void scan_keypad()
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
				if (col == 4 && row == 0)	//Middle C
				{
					NOTE_ON;
					_delay_us(23982);
					NOTE_OFF;
					_delay_us(23982);
				}
				else if (col == 4 && row == 1)	//C# Db
				{
					NOTE_ON;
					_delay_us(22637);
					NOTE_OFF;
					_delay_us(22637);
				}
				else if (col == 4 && row == 2)	//D
				{
					NOTE_ON;
					_delay_us(21366);
					NOTE_OFF;
					_delay_us(21366);
				}
				else if (col == 4 && row == 3)	//D# Eb
				{
					NOTE_ON;
					_delay_us(20167);
					NOTE_OFF;
					_delay_us(20167);
				}
				else if (col == 5 && row == 0) //E
				{
					NOTE_ON;
					_delay_us(19035);
					NOTE_OFF;
					_delay_us(19035);
				}
				else if (col == 5 && row == 1)	//F
				{
					NOTE_ON;
					_delay_us(17966);
					NOTE_OFF;
					_delay_us(17966);
				}
				else if (col == 5 && row == 2)	//F# Gb
				{
					NOTE_ON;
					_delay_us(16958);
					NOTE_OFF;
					_delay_us(16958);
				}
				else if (col == 5 && row == 3)	//G
				{
					NOTE_ON;
					_delay_us(16006);
					NOTE_OFF;
					_delay_us(16006);
				}
				else if (col == 6 && row == 0)	//G# Ab
				{
					NOTE_ON;
					_delay_us(15108);
					NOTE_OFF;
					_delay_us(15108);
				}
				else if (col == 6 && row == 1)	//A
				{
					NOTE_ON;
					_delay_us(14260);
					NOTE_OFF;
					_delay_us(14260);
				}
				else if (col == 6 && row == 2)	//A# Bb
				{
					NOTE_ON;
					_delay_us(13460);
					NOTE_OFF;
					_delay_us(13460);
				}
				else if (col == 6 && row == 3)	//B
				{
					NOTE_ON;
					_delay_us(12704);
					NOTE_OFF;
					_delay_us(12704);
				}
				else if (col == 7 && row == 0)	//C5
				{
					NOTE_ON;
					_delay_us(11991);
					NOTE_OFF;
					_delay_us(11991);
				}
				else if (col == 7 && row == 1)	//C# Db
				{
					NOTE_ON;
					_delay_us(11526);
					NOTE_OFF;
					_delay_us(11526);
				}
				else if (col == 7 && row == 2)	//D
				{
					NOTE_ON;
					_delay_us(10683);
					NOTE_OFF;
					_delay_us(10683);
				}
				else if (col == 7 && row == 3)	//D# Eb
				{
					NOTE_ON;
					_delay_us(10083);
					NOTE_OFF;
					_delay_us(10083);
				}
			}
		}
	}
}