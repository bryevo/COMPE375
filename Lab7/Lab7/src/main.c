#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define CPU_Freq 16000000UL
#define Prescalar CPU_Freq/2048
#define LED_ON  PORTB |=(1<<PORTB5)
#define LED_OFF PORTB &= ~(1<<PORTB5)
#define LED_TOGGLE PINB |= (1<<PINB5)
//REDID XXXXXX487
#define X 4
#define Y 8
#define Z 7

void INIT_PWM(int b);
void milliS_timer1(uint8_t ms);

int button = '\0';	//set to non-null value

int main(void)
{
	//Column 0-3
	DDRD |= (1<<DDD4);
	DDRD |= (1<<DDD5);
	DDRD |= (1<<DDD6);
	DDRD |= (1<<DDD7);
	DDRB |= (1<<DDB5);
	DDRB &= ~(1<<DDB7);
	
	DDRC |= (1<<DDC5); // C5 for output
	PCMSK0 |= (1<<PCINT7);
	PCICR |= (1<<PCIE0);
	sei();	//Start interrupt
	
	milliS_timer1(X);
	
	while(1)
	{
		INIT_PWM(button);
		
		UCSR0B = (0<<TXEN0);
	}
}

void INIT_PWM(int b)
{
	TCCR1B|= (1<<CS10)  |  (1<<WGM12) ;
	TIMSK1 |= (1<<OCIE1A)   | (1<<OCIE1B);
	OCR1A = (Z+1) * 100;   //PWM Frequency
	OCR1B = ((Z+1)*10) * b; //duty
}

void milliS_timer1(uint8_t ms)
{
	uint16_t freq = 1/ (2*(ms*.001));
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02) | (1<<CS00);
	OCR0A = ms * Prescalar;
	OCR0B = ms * Prescalar;
	TIMSK0 |= (1<<OCIE0A);
	TIMSK0 |= (1<<OCIE0B);
}

ISR(PCINT0_vect)
{
	PCMSK0 &= ~(1<<PCINT7);
	LED_TOGGLE;
	TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	PCMSK0 |= (1<<PINB7);
	TIMSK0 &= ~(OCIE1A);
}

ISR(TIMER0_COMPB_vect)
{
	PORTD = 0b11011111;
	if(!bit_is_set(PIND, 0))
		button = 1;
	if(!bit_is_set(PIND, 1))
		button = 5;
	if(!bit_is_set(PIND, 2))
		button = 8;
	if(!bit_is_set(PIND, 3))
		button = 0;
	
	PORTD = 0b10111111;
	if(!bit_is_set(PIND, 0))
		button = 2;
	if(!bit_is_set(PIND, 1))
		button = 6;
	if(!bit_is_set(PIND, 2))
		button = 9;
	if(!bit_is_set(PIND, 3))
		button = '\0';
	
	PORTD = 0b01111111;
	if(!bit_is_set(PIND, 0))
		button = 3;
	if(!bit_is_set(PIND, 1))
		button = '\0';
	if(!bit_is_set(PIND, 2))
		button = '\0';
	if(!bit_is_set(PIND, 3))
		button = '\0';
	
	PORTD = 0b11101111;
	if(!bit_is_set(PIND, 0))
		button = '\0';
	if(!bit_is_set(PIND, 1))
		button = 4;
	if(!bit_is_set(PIND, 2))
		button = 7;
	if(!bit_is_set(PIND, 3))
		button = '\0';	
}

ISR(TIMER1_COMPA_vect)
{
	PORTC |=(1<<PINC5);
}

ISR(TIMER1_COMPB_vect)
{
	PORTC &= ~(1<<PINC5);
}