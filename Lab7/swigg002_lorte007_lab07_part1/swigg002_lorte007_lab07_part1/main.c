/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #7  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

enum States{Start, Init, Inc, Inc_Wait, Dec, Dec_Wait, Reset, Reset_Wait}state;
unsigned char button;
unsigned char value = 0x00;
unsigned char count = 0;
void Tick(){
	button = (~PINA) & 0x03;
	switch(state){
		case Start:
			LCD_Cursor(1);
			LCD_WriteData( value + '0' );
			state = Init;
			break;
		case Init:
			if(button == 0x02){
				state = Dec;
			}
			else if(button == 0x01){
				state = Inc;
			}
			break;
		case Inc:
			if(value < 9){
				value++;
			}
			LCD_Cursor(1);
			LCD_WriteData(value + '0');
			state = Inc_Wait;
			break;
		case Inc_Wait:
			if(button == 0x03){
				count = 0;
				state = Reset;
			}
			else if(button == 0){
				count = 0;
				state = Init;
			}
			else if((button == 0x01) & (count == 10)){
				state = Inc;
				count = 0;
			}
			else{
				state = Inc_Wait;
				count++;
			}
			break;
		case Dec:
			if(value > 0){
				value--;
			}
			LCD_Cursor(1);
			LCD_WriteData(value + '0');
			state = Dec_Wait;
			break;
		case Dec_Wait:
			if(button == 0x03){
				count = 0;
				state = Reset;
			}
			else if(button == 0){
				count = 0;
				state = Init;
			}
			else if((button == 0x02) & (count == 10)){
				state = Dec;
				count = 0;
			}
			else{
				state = Dec_Wait;
				count++;
			}
			break;	
		case Reset:
			value = 0;
			LCD_Cursor(1);
			LCD_WriteData(value + '0');
			state = Init;
			break;
		default:
			state = Start;
			break;
			
	}
}

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00; 
	DDRA = 0x00; PORTA = 0xFF;

	LCD_init();  
	TimerSet(100);
	TimerOn();
	
	state = Start;

    while (1) 
    {
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
		continue;
    }
}

