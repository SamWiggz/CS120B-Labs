/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #5 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


enum States{Start, WaitHash, EnterCombo, Unlock, Lock1, Lock2}state;
char list[4] = {0,0,0,0};	
	
void tick(){
	switch(state){
		case Start:
			state = WaitHash;
			break;
		case WaitHash:
			//state = ((PINA & 0x04) == 0x04)?EnterCombo:WaitHash; 
			if((PINA & 0x04) == 0x04){
				list[0] = 0x04;				
				state = EnterCombo;
			}
			else{
				state = WaitHash;
			}
			break;
		case EnterCombo:
			//state = ((PINA & 0x02) == 0x02)?Unlock:WaitHash;
			if(((PINA & 0x04) == 0x04) && (list[0] == 0x04)){		//loop state waiting for the first x	
				state = EnterCombo;
			}
			else if(((PINA & 0x01) == 0x01) && (list[0] == 0x04) && (list[2] == 0)){
				list[1] = 0x01;				
				state = EnterCombo;
			}
			else if(((PINA & 0x02) == 0x02) && (list[0] == 0x04) && (list[1] == 0x01) && (list[2] == 0x00)){
				list[2] = 0x02;				
				state = EnterCombo;

			}
			else if(((PINA & 0x02) == 0x02) && (list[0] == 0x04) && (list[1] == 0x01) && (list[2] == 0x02)){  //loops state	
				state = EnterCombo;
			}			
			else if(((PINA & 0x01) == 0x01) && (list[0] == 0x04) && (list[1] == 0x01) && (list[2] == 0x02) && (list[3] == 0x00)){
				list[3] = 0x01;				
				state = Unlock;
			}
			else{
				list[0] = 0x00;
				list[1] = 0x00;
				list[2] = 0x00;
				list[3] = 0x00;
				state = WaitHash;
			}
			break;
		case Unlock:
			list[0] = 0x00;
			list[1] = 0x00;
			list[2] = 0x00;
			list[3] = 0x00;			
			state = Lock1;
			break;
		case Lock1:
			if((PINA & 0x80) == 0x80){				
				state = WaitHash;
			}
			else if((PINA & 0x04) == 0x04){
				list[0] = 0x04;					
				state = Lock2;
			}
			else{
				state = Lock1;
			}
			break;
		case Lock2:
			if(((PINA & 0x04) == 0x04) && (list[0] == 0x04)){		//loop state waiting for the first x	
				state = Lock2;
			}
			else if(((PINA & 0x01) == 0x01) && (list[0] == 0x04) && (list[2] == 0)){
				list[1] = 0x01;				
				state = Lock2;
			}
			else if(((PINA & 0x02) == 0x02) && (list[0] == 0x04) && (list[1] == 0x01) && (list[2] == 0x00)){
				list[2] = 0x02;				
				state = Lock2;

			}
			else if(((PINA & 0x02) == 0x02) && (list[0] == 0x04) && (list[1] == 0x01) && (list[2] == 0x02)){  //loops state	
				state = Lock2;
			}			
			else if(((PINA & 0x01) == 0x01) && (list[0] == 0x04) && (list[1] == 0x01) && (list[2] == 0x02) && (list[3] == 0x00)){
				list[3] = 0x01;				
				state = WaitHash;
			}
			else{
				list[0] = 0x00;
				list[1] = 0x00;
				list[2] = 0x00;
				list[3] = 0x00;
				state = Lock1;
			}
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
		case Lock1:
			PORTC = 0x04;
			break;
		case Lock2:
			PORTC = 0x05;
			break;
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

