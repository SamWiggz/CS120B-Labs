/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum States{Start, Init, Wait, Inc, Dec, Rest} state;

void Tick(){
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			state = Wait;
			break;
		case Wait:
			if((PINA == 0x01) && (PORTC < 0x09)){
				state = Inc;
			}else if((PINA == 0x02) && (PORTC > 0x00)){
				state = Dec;
			}else if(PINA == 0x03) {
				state = Rest;
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
			PORTC = 0x07;
			break;
		case Wait:
			break;
		case Inc:
			PORTC = PORTC + 1;
			break;
		case Dec:
			PORTC = PORTC - 1;
			break;
		case Rest:
			PORTC = 0x00;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Replace with your application code */
    
	state = Start;
	while (1) 
    {
		Tick();
    }
}

