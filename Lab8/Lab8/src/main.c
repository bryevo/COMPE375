#include <avr/io.h>
#include <avr/interrupt.h>

#define FOSC 16000000 // Clock Speed
#define LightOn PORTB |= (1<<PORTB5)
#define LightOff PORTB &= ~(1<<PORTB5)
#define Toggle PORTB ^= (1<<PORTB5);

void timer1_init();
void timer0_init();
void ADC_init();
void PWM_INIT_LED();

uint16_t duty;
int adc_start = 0;

int main(void)
{
	DDRB |= (1<<DDB5);	// Output for Z Frequency
	DDRB |= (1 << DDB4);	// Output for X
	timer1_init();	// Timer for PWM
	timer0_init();	// Timer for Xms
	
	while(1)
	{
		OCR1B = duty;
	}
}



void timer0_init()		//X ms
{
	TCCR0B |= (1 << WGM02) | (1 << CS02) | (1 << CS00);	//Set up timer with prescaler = 1024 and CTC Mode
	
	TCNT0 = 0;	//Initialize Counter
	
	OCR0A = 139;		//4 ms  ((16MHz/1024)*(4ms))-1
	
	TIMSK0 |= (1 << OCIE1A);	//Enable Compare A
	sei();
	
	
}
void timer1_init()	//Z frequency
{
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);	//Set up timer with prescaler = 64 and CTC Mode
	
	TCNT1 = 0;	//Initialize Counter
	
	OCR1A = 276;	//Will change the top to 900Hz frequency  (16MHz/(64*900))-1
	
	TIMSK1 |= (1 << OCIE1A)| (1<< OCIE1B) ; //Enable Compare A and B
	
	sei();
	
}
void ADC_init(void)
{
	//Single Conversion Mode
	ADMUX |= (1 << REFS0) | (1 << MUX0) | (1 << MUX1) | (1 << MUX2); //voltage reference/ channel bits
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 <<ADATE) | (1 << ADIE) | (1 << ADPS2) | ( 1 << ADPS1);	//Free running select/ start conversion/ Interrupt enable/ frequecny bits 
}

ISR(ADC_vect)
{
	duty = ADC;
	OCR1B = duty;
}

ISR(TIMER1_COMPA_vect)
{
	LightOn;		//PortB5 (LED light on)
}
ISR(TIMER1_COMPB_vect)
{
	LightOff;		//PortB5 (LED light off)
}
ISR(TIMER0_COMPA_vect)
{
	if(adc_start == 0)
	{
		ADC_init();
		adc_start++;
	}
	
	PORTB ^= (1<<PORTB5);		//Toggle LED
	
}