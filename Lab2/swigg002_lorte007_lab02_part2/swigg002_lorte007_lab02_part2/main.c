/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #2  Exercise #2 
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
	DDRC = 0x00;
	PORTA = 0x00;
	PORTC = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char cntavail;
    while (1) 
    {
		tmpA = PINA & 0x0F;
		cntavail = 0x00; 
		for(unsigned char i = 0; i < 4; i++){
			  if (GetBit(tmpA, i)){
				  cntavail++;
			  }
		}
		tmpC = 0x04 - cntavail;
		
		PORTC = tmpC;
    }
	return 0;
}

