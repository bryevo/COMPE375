#include<avr/io.h>
#include<asf.h>
#include<string.h>
#include<util/delay.h>
#define F_CPU 16000000UL
//#define FOSC 16000000 //Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define ALARM_ON PORTB |= (1<<PORTB5);
#define ALARM_OFF PORTB &= ~(1<<PORTB5);	

bool detect = false;
char key[25] = "Intruder Detected!\r\n";
void Detect_Motion();
void USART_Init(unsigned int ubrr);
bool USART_Transmit(const char ch[]);
int main()
{
	DDRC &= ~(1<<PINC0);	//setting PINC0 as an input
	PORTC |= (1<<PINC0);
	DDRB |= 0x00;
	DDRB |= (1<<DDB5);
	PORTB |= 0x0F;	//Low nibble
	USART_Init(MYUBRR);
	while(1)
		Detect_Motion();
	return 0;
}

void Detect_Motion() {
	if (PINC&(1<<0)) //if PINC0 is active
	{
		detect = USART_Transmit(key);	//transmit text key
		while (PINC&(1<<0)){	//while PINC0 is still active
			ALARM_ON;	//Sound alarm
			_delay_us(10000);
			ALARM_OFF;
			_delay_us(10000);
			if(!(PINB & (1<<PINB7))) {	//toggle off the alarm/led
				for (int i = 0; i < 36; i++)
					_delay_ms(1000);
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
bool USART_Transmit(const char ch[])	//
{
	
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	for (int i = 0; i < strlen(ch); i++)	//for each character in the array
	{
	_delay_ms(25);
	UDR0 = ch[i];          //Transmit the char index	
	}
}