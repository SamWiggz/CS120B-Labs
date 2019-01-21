/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum States {Start, On, Off}state;

// unsigned char tempA;

void Tick(){
	switch (state){ //transitions
		case Start:
			state = On;
			break;
		case On:
			state = PINA? Off: On;
			/*if (PINA == 0x01){
				state = Off;
			}else{
				state = On;
			}*/
			break;
		case Off:
			state = PINA? Off: On;
			/*if (PINA == 0x00){
				state = On;
			}else{
				state = Off;
			}*/
			break;
		default:
			state = Start;
			break;
	}switch (state){ //state actions
		case Start:
			break;
		case On:
			PORTB = 0x01;
			break;
		case Off:
			PORTB = 0x02;
			break;
		default:
			break;
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
    while (1) 
    {
		// tempA = PINA;
		Tick();
    }return 0;
}

