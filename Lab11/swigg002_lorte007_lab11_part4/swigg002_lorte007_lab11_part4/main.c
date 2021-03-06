/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #11  Exercise #4 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include <stdio.h>
#include "io.c"
#include "io.h"
#include "keypad.h"
#include "scheduler.h"

unsigned char tmpB = 0x1F;
unsigned char cursorCount = 1;


enum SM1_States{SM1_output};

int SMTick1(int state){
	unsigned char x;
	x = GetKeypadKey();
	switch(state){
		case SM1_output:
		switch (x) {
			case '\0':
				if(tmpB != 0x1F){
					LCD_Cursor(cursorCount); LCD_WriteData(tmpB + '0'); cursorCount++;
					tmpB = 0x1F;
				}
				tmpB = 0x1F;	
				break;
			case '1':
				tmpB = 0x01;
				break; 
			case '2':
				tmpB = 0x02;
				break;
			case '3':
				tmpB = 0x03;
				break;
			case '4':
				tmpB = 0x04;
				break;
			case '5':
				tmpB = 0x05;
				break;
			case '6':
				tmpB = 0x06;
				break;
			case '7':
				tmpB = 0x07;
				break;
			case '8':
				tmpB = 0x08;
				break;
			case '9':
				tmpB = 0x09;
				break;
			case 'A':
				tmpB = 0x0A + 0x37 - '0';
				break;
			case 'B':
				tmpB = 0x0B + 0x37 - '0';
				break;
			case 'C':
				tmpB = 0x0C + 0x37 - '0';
				break;
			case 'D':
				tmpB = 0x0D + 0x37 - '0';
				break;
			case '*':
				tmpB = 0x0E + 0x1C - '0';
				break;
			case '0':
				tmpB = 0x00;
				break;
			case '#':
				tmpB = 0x0F + 0x14 - '0';
			break;
			default: tmpB = 0x1B; break; // Should never occur. Middle LED off.
		}
		if(cursorCount==17){
			cursorCount=1;
		}
		state = SM1_output;
		PORTB=tmpB;
		break;
	}
	return state;
}


int main()
{

	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; 
	DDRD = 0xFF; PORTD = 0x00;
	// Period for the tasks
	unsigned long int SMTick1_calc = 50;


	//Calculating GCD
	unsigned long int tmpGCD = 1;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = 0;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &SMTick1;//Function pointer for the tick.


	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	LCD_DisplayString(1,"Congratulations");

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;
}

