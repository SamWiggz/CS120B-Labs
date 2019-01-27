/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum States{Start, Init, Wait, Inc, Dec, Rest, Wait2} state;

void Tick(){
 	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			state = Wait;
			break;
		case Wait:
			if(((~PINA & 0x03) == 0x01) && (PORTB < 0x09)){
				state = Inc;		
			}else if(((~PINA & 0x03) == 0x02) && (PORTB > 0x00)){
				state = Dec;
			}else{
				state = Wait2;
			} 
			break;
		case Inc:
			PORTB = PORTB + 0x01;
			state = Wait2;
			break;
		case Dec:
			PORTB = PORTB - 0x01;
			state = Wait2;
			break;
		case Rest:
			PORTB = 0x00;
			state = Wait2;
			break;
		case Wait2:
			//state = (button == 0x00)? Wait: Wait2;
			if((~PINA & 0x03) == 0x00){
				state = Wait;
			}
			else if((~PINA & 0x03) == 0x03){
				state = Rest;
			}
			else{
				state = Wait2;
			}
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
			break;
		case Dec:
			break;
		case Rest:
			break;
		case Wait2:
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
	while (1) 
    {
		Tick();
    }
}