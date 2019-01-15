/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	
	unsigned char count;
	unsigned char i;
    /* Replace with your application code */
    while (1) 
    {
		count = 0;
		for(i = 0; i < 8; i++){
			if(GetBit(PINA,i)){
				count++;	
			}
			if(GetBit(PINB,i)){
				count++;
			}
		}
		PORTC = count;
    }
	return 0;
}

