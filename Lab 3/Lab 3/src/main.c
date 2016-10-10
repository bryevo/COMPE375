//
//  main.c
//  Lab 3
//
//  Created by Brian Vo on 9/20/16.
//  Copyright © 2016 Brian Vo. All rights reserved.
//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

void delay(float x);
void increaseBrightness(void);
void decreaseBrightness(void);

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
void delay(float x) {		//delay for inc/dec brightness function
	x = x * 25;
	for (int i = 0; i < x; i++) {
	_delay_us(1);
	}
}