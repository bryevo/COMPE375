/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
 
 //
 //  main.c
 //  MorseCodeSort
 //
 //  Created by Brian Vo on 9/9/16.
 //  Copyright © 2016 Brian Vo. All rights reserved.
 //

#include <asf.h>
#define F_CPU 16000000UL // 16MHz clock from the debug processor
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void sortRedID(char *val);
void blink(char *sort);
void shortBlink();
void longBlink();
void space();

int main() {
	DDRB |= (1<<DDB5);
	static const char student[] = "Brian Vo 819606487";
	sortRedID(student);
}

void blink(char *sort) {
	int i = 0;
	while (i < strlen(sort)) {
		if (sort[i] == '.'){
		shortBlink();
		}
		else if (sort[i] == '-') {
		longBlink();
		}
		else {
		space();
		}
		i++;
	}
}

void shortBlink() {
	PORTB |= (1<<PORTB5); //Dot
	_delay_ms(200);
	PORTB &= (0<<PORTB5); //Off
	_delay_ms(100);
}

void longBlink() {
	PORTB |= (1<<PORTB5); //Dash
	_delay_ms(600);
	PORTB &= (0<<PORTB5); //Off
	_delay_ms(100);
}

void space() {
	_delay_ms(1000);
}

void sortRedID(char *val) {
	char str[100];
	for (int i = 0; i < strlen(val); i++) {
		switch(toupper(val[i])) {
			case 'A': strcat(str, ".-"); break;
			case 'B': strcat(str, "-..."); break;
			case 'C': strcat(str, "-.-."); break;
			case 'D': strcat(str, "-.."); break;
			case 'E': strcat(str, "."); break;
			case 'F': strcat(str, "..-."); break;
			case 'G': strcat(str, "--."); break;
			case 'H': strcat(str, "...."); break;
			case 'I': strcat(str, ".."); break;
			case 'J': strcat(str, ".---"); break;
			case 'K': strcat(str, "-.-"); break;
			case 'L': strcat(str, ".-.."); break;
			case 'M': strcat(str, "--"); break;
			case 'N': strcat(str, "-."); break;
			case 'O': strcat(str, "---"); break;
			case 'P': strcat(str, ".--."); break;
			case 'Q': strcat(str, "--.-"); break;
			case 'R': strcat(str, ".-."); break;
			case 'S': strcat(str, "..."); break;
			case 'T': strcat(str, "-"); break;
			case 'U': strcat(str, "..-"); break;
			case 'V': strcat(str, "...-"); break;
			case 'W': strcat(str, ".--"); break;
			case 'X': strcat(str, "-..-"); break;
			case 'Y': strcat(str, "-.--"); break;
			case 'Z': strcat(str, "--.."); break;
			case '0': strcat(str, "-----"); break;
			case '1': strcat(str, ".----"); break;
			case '2': strcat(str, "..---"); break;
			case '3': strcat(str, "...--"); break;
			case '4': strcat(str, "....-"); break;
			case '5': strcat(str, "....."); break;
			case '6': strcat(str, "-...."); break;
			case '7': strcat(str, "--..."); break;
			case '8': strcat(str, "---.."); break;
			case '9': strcat(str, "----."); break;
			case ' ': strcat(str, " "); break;
		}
	}
	blink(str);
}