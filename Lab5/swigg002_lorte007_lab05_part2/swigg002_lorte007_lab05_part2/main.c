/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum States{Start, Init, Wait, Inc, Dec, Rest} state;
	
unsigned char tempA;

void Tick(){
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			state = Wait;
			break;
		case Wait:
			if((tempA == 0x01) && (PORTB < 0x09)){
				state = Inc;
				break;
			}else if((tempA == 0x02) && (PORTB > 0x00)){
				state = Dec;
				break;
			}else if(tempA == 0x03) {
				state = Rest;
				break;
			}else{
				state = Wait;
			} break;
		case Inc:
			state = Wait;
			break;
		case Dec:
			state = Wait;
			break;
		case Rest:
			state = Wait;
			break;
		default:
			state = Start;
			break;
	}switch (state){
		case Start:
			break;
		case Init: 
			PORTB = 0x07;
			break;
		case Wait:
			break;
		case Inc:
			PORTB = PORTB + 0x01;
			break;
		case Dec:
			PORTB = PORTB - 0x01;
			break;
		case Rest:
			PORTB = 0x00;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Replace with your application code */
    
	state = Start;
	tempA = ~PINA;
	while (1) 
    {
		Tick();
    }
}