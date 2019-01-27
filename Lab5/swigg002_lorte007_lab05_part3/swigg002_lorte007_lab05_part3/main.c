/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
unsigned char button = 0x00;

enum States{Start, Init, Wait1, Pause1, GoUp, Wait2, Pause2, GoDown}state;
void Tick(){
	switch(state){ //transition
		case Start:
			state = Init;
			break;
		case Init:
			state = Wait1;
			break;
		case Wait1:
			if(button){
				PORTB = PORTB * 2;				
				state = GoUp;
			}
			else
				state = Wait1;
			break;
		case Pause1:
			state = (button == 0)?GoUp:Pause1;
			break;
		case GoUp:
			if((button == 0x00) && (PORTB < 0x80)){
				state = Wait1;
			}
			else if((button == 0x00) && (PORTB == 0x80)){
				state = Wait2;
			}
			else
				state = GoUp;
			break;
		case Wait2:
			if(button){
				PORTB = PORTB / 2;
				state = GoDown;
			}
			else
				state = Wait2;
			break;
		case Pause2:
			state = (button==0)?GoDown:Pause2;
			break;
		case GoDown:
			if((button == 0x00) && (PORTB > 0x01)){
				state = Wait2;
			}
			else if((button == 0x00) && (PORTB == 0x01)){
				state = Wait1;
			}
			else
				state = GoDown;
			break;			
		default:
			state = Start;
			break;
	}
	switch(state){ //state action
		case Start:
			break;
		case Init:
			PORTB = 0x01;
			break;
		case Wait1:
			button = ~PINA & 0x01;
			break;
		case Pause1:
			button = ~PINA & 0x01;
			break;		
		case GoUp:
			button = ~PINA & 0x01;
			break;	
		case Wait2:
			button = ~PINA & 0x01;
			break;
		case Pause2:
			button = ~PINA & 0x01;
			break;
		case GoDown:
			button = ~PINA & 0x01;
			break;
		default:
			break;
	}
}
int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	state = Start;
    while (1) 
    {
		Tick();
    }
}

