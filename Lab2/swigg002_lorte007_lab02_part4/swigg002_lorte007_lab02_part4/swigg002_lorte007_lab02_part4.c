/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #2  Exercise #4 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <math.h>

int main(void)
{
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
		
	unsigned char realWeight = 0x00;
	unsigned char shiftedWeight = 0x00;
		
	unsigned char tmpD = 0x00;
	
    while (1) 
    {
		realWeight = PINA + PINB + PINC;
		if (realWeight > 140){
			tmpD = (tmpD & 0xFE) | 0x01;
		}
		if ( abs(PINA - PINC) > 80){
			tmpD = (tmpD & 0xFD) | 0x02;
		}
		
		shiftedWeight = realWeight * 4; //need to shift left two times 
		tmpD = tmpD | shiftedWeight;
		PORTD = tmpD;		
    }
	return 0;
}

