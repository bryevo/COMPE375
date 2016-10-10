#define FOSC 16000000 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <asf.h>


void USART_Init(unsigned int ubrr);
void USART_Receive(unsigned char* REDID);
void USART_Transmit(unsigned char REDID);

void USART_Init( unsigned int ubrr)
{
	/*baud rate*/
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	
	/*receiver and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/*frame format: 8data, 2stop bit*/
	UCSR0C = (3<<UCSZ00);
	
}

int main(void)
{
	char REDID[] = " 816906487\r\n";  //816906487 is my ID number and will put it into the array
	USART_Init(MYUBRR);
	while(1)                          //this will continuously loop the array in putty
	{
		USART_Receive(REDID);        //this function calls the USTART receiver
		_delay_ms(500);
	}
	
}



void USART_Receive(unsigned char *REDID)
{
	for(*REDID = 1; *REDID != 0x00; REDID++) //This calls the USTART_Transmit and recieves it byte by byte
	{
		USART_Transmit(*REDID);
	}
}


void USART_Transmit(unsigned char REDID)
{
	
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	
	UDR0 = REDID;                                   //This returns the char to the string
	
}