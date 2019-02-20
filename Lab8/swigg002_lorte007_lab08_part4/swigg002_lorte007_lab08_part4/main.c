/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #8  Exercise #4 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>



void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
    /* Replace with your application code */
    while (1) 
    {
		unsigned char MAX = 0x2F;
		unsigned short x = ADC; 
		if(x  >= (MAX)){
			PORTB = 0xFF;
		}
		if( x == 0x27){
			PORTB = 0x7F;
		}
		if ( x == 0x26){
			PORTB = 0x3F;
		}
		if ( x == 0x25){
			PORTB = 0x1F;
		}
		if ( x == 0x24){
			PORTB = 0x0F;
		}
		if ( x == 0x23){
			PORTB = 0x07;
		}
		if ( x == 0x22){
			PORTB = 0x03;
		}
		if ( x == 0x21){
			PORTB = 0x01;
		}	
		if ( x == 0x20){
			PORTB = 0x00;
		}	
    }
	return 0;
}

