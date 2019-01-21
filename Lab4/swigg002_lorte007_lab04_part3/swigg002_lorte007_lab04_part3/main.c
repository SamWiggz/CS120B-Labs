/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #3 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


enum States{Start, WaitHash, EnterCombo, Unlock, Lock}state;
	
void tick(){
	switch(state){
		case Start:
			state = WaitHash;
			break;
		case WaitHash:
			state = ((PINA & 0x04) == 4)?EnterCombo:WaitHash; 
			break;
		case EnterCombo:
			state = ((PINA & 0x02) == 2)?Unlock:WaitHash;
			break;
		case Unlock:
			state = Lock;
			break;
		case Lock:
			state = ((PINA & 0x80) == 0x80)?WaitHash:Lock;
			break;
		default:
			state = Start;
			break;
	}
	
	switch(state){
		case Start:
			PORTC = 0x00;
			break;
		case WaitHash:
			PORTB = 0x00;
			PORTC = 0x01;
			break;
		case EnterCombo:
			PORTC = 0x02;
			break;
		case Unlock:
			PORTC = 0x03;
			PORTB = 0x01;
			break;
		case Lock:
			PORTC = 0x04;
		default:
			break;
	}
}

int main(void)
{
    DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
    while (1) 
    {
		tick();
    }
	return 0;
}

