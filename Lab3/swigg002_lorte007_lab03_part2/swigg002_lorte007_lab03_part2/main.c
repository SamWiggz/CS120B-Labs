/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #2 
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
    /* Replace with your application code */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	
	unsigned char tank;
	unsigned char tmpC = 0x00;
	
    while (1) 
    {
			tank = PINA & 0x0F;
			
			if((tank == 0x01) || (tank == 0x02)){
				tmpC = 0x60;
			}
			else if ((tank == 0x03) || (tank == 0x04)){
				tmpC = 0x70;
			}
			else if ((tank == 0x05) || (tank == 0x06)){
				tmpC = 0x38;
			}
			else if ((tank == 0x07) || (tank == 0x08) || (tank == 0x09)){
				tmpC = 0x3C;
			}
			else if ((tank == 0x0A) || (tank == 0x0B) || (tank == 0x0C)){
				tmpC = 0x3E;
			}
			else if ((tank == 0x0D) || (tank == 0x0E) || (tank == 0x0F)){
				tmpC = 0x3F;
			}
			PORTC = tmpC;
    }
	return 0;
}

