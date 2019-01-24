/*	Partn
er(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: lab5
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	unsigned char button = 0x00;
	unsigned char led = 0x00; 
	
    while (1) 
    {
		button = ~PINA & 0x01;
		if(button){
			led = 0xFF;
		}
		else{
			led = 0x00;
		}
		PORTC = led;
    }
}

