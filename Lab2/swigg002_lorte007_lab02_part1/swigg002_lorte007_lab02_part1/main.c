/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #2  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0x00; 
	unsigned char tmpB = 0x00; 
	unsigned char tmpA = 0x00;
	while (1) 
    {
		tmpA = PINA & 0x03;
		if(tmpA == 0x01){
			tmpB = (tmpB & 0xFE) | 0x01;
		}
		else{
			tmpB = (tmpB & 0xFE);	
		}
		PORTB = tmpB;
	}
	return 0;
}

