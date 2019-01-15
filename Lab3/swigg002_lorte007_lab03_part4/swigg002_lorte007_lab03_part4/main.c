/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #4 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}
int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
	
	unsigned char i;
	
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		for(i = 0; i < 4; i++){
			if(GetBit(PINA,i)){
				tmpC = SetBit(tmpC, i+4, 1);
			}
		}
		for(i = 4; i < 8; i++){
			if(GetBit(PINA,i)){
				tmpB = SetBit(tmpB, i-4, 1);
			}
		}
		PORTB = tmpB;
		PORTC = tmpC;
    }
	
	return 0;
}

