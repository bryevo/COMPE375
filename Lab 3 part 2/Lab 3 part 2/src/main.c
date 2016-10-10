//
//  main.c
//  Lab 3 part 2
//
//  Created by Brian Vo on 9/20/16.
//  Copyright _ 2016 Brian Vo. All rights reserved.
//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

void delay(int x);
void increaseBrightness(void);
void decreaseBrightness(void);
void milliS_timer(uint8_t milliS);
void PWM_Init();

int main(void) {
	DDRB |= (1<<DDB5);		//Set port bit B5 in data direction register to 1: an Output
	DDRB &= ~(1<<DDB7);		//Set port bit B7; 0
	int button = 0;			//integer to set initial starting point; button is not pressed
	while(1) {
		if(!(PINB & (1<<PINB7))) {	//if button pressed/held
			increaseBrightness();
			button = 1;				//button pressed
			if(!(PINB & (1<<PINB7)) && button == 1) {	//returns true if buttons held and was pressed
				while(1){
					PORTB |= (1<<PORTB5); // Set port bit B5 to 1 to turn on the LED
					if(PINB & (1<<PINB7)) {		//if button is let go, break loop
						break;
					}
				}
			}
		}
		while((PINB & (1<<PINB7)) && button == 1) {		//button is let go and was pressed
			decreaseBrightness();
			button = 0;		//reset to starting point
		}
	}
}

void increaseBrightness() {
	int x = 100;		// max limit value
	while(x >= 0) {
		PORTB |= (1<<PORTB5);		//Turn 6th bit on PORTB (i.e. PB5) to 1; on
		_delay_ms(1);
		PORTB &= (0<<PORTB5);		//set PORTB5 to 0;
		delay(x);
		x -= 1;
	}
}

void decreaseBrightness() {
	int x = 1;
	while(x <= 100) {
		PORTB |= (1<<PORTB5);
		_delay_ms(1);
		PORTB &= (0<<PORTB5);
		delay(x);
		x += 1;
	}
}
void delay(int x) {		//delay for inc/dec brightness function
	for (int i = 0; i < x; i++) {
		PWM_Init();
		milliS_timer(1);
		//wait till timer expire
		while (!(TIFR1 & (1<<OCF1A)));
		TIFR1 = (1<<OCF1A);		//clear the flag
		//stop timer
	}
}

void PWM_Init(){
	TCCR1B |= (1<<CS10) | (1<<WGM12);
	TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);
	//OCR1A = (F_CPU/(freq*2*256)-1);
	OCR1A = 8000;		//Sets  CTC output compare value
}

void milliS_timer(uint8_t milliS){
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02) | (1<<CS00);
	OCR0A = milliS*7,8125-1;
	TIMSK0 = (1<<OCIE0A);
}
