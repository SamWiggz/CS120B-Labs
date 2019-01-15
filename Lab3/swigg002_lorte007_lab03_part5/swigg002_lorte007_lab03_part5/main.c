/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #5 
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
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFE;
	PORTB = 0x01;
	
	unsigned char lower = 0x00;
	unsigned char tmpD = 0x00;
	unsigned char tmpB;
	unsigned char totalWeight = 0x00;
    /* Replace with your application code */
    while (1)
    {
		tmpB = 0x00;
		tmpD = PIND;
		lower = PINB;
		totalWeight = (tmpD << 1) | lower;
		if(totalWeight >= 70){
			tmpB = SetBit(tmpB, 1, 1);
		}
		else if((totalWeight < 70) && (totalWeight > 5)){
			tmpB = SetBit(tmpB, 2, 1);
		}
		else if(totalWeight <= 5){
			tmpB = SetBit(tmpB, 2, 0);
			tmpB = SetBit(tmpB, 1, 0);
		}
		PORTB = tmpB;
		
    }
	return 0;
}

