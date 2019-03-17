/*	Name & E-mail: Samuel Wiggins (swigg002@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Final Project
 *	Exercise Description: [optional - include for your own benefit]
 *			Avoid the Car AVR Code, Only needed one state machine since the rest of the code is on the Arduino
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "timer.h"
#include "io.c"
#include "io.h"
#include "usart.h"



void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


unsigned short tmpA = 0x0000; //to hold large ADC value
unsigned char tmpC  = 0x00;
unsigned char score = 0;
char scoreArr[4];

enum State{Start, Reset, On}state;
	
unsigned char init = 0x00;	

void tick(){
	switch(state){
		case Start:
			state = Reset;
			break;
		case Reset:
			if(init == 0x00){
				if(((~PINB) & 0x01) == 0x01){
					state = On;
					init = 1;
				}
				else{
					state = Reset;
				}
			}
			else{
				state = On;
				score = 0;
			}
			break;
		case On:
			if(((~PINB) & 0x01) == 0x01){
				state = Reset;
			}		
			else{
				state = On;
			}	
			break;
		default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			break;
		case Reset:
			if(init == 0x00){
				LCD_DisplayString(1, "Press To Start");	//start game lcd
			}
			break;
		case On:
			itoa(score, scoreArr, 10);	//used to write value to LCD screen
			LCD_DisplayString(1, "Time: ");
			LCD_Cursor(7);
			LCD_WriteData(scoreArr[0]);
			if(score>9){
				LCD_WriteData(scoreArr[1]);
			}
			if(score>99){
				LCD_WriteData(scoreArr[2]);
			}	
			if(score>999){
				LCD_WriteData(scoreArr[3]);
			}		
			tmpC = 0x00;
			if(ADMUX == 1){ 	//switch between ADC 1 -> ADC 0   switches between u/d to l/r
				ADMUX = 0;
			}
			else if(ADMUX == 0){ 	//switch between ADC 0 -> ADC 1
				ADMUX = 1;
			}
			
			tmpA = ADC;		// value ranges from 0 to 1024(2^10)
			

			if(ADMUX == 0 && tmpA < 50){//right
				tmpC = 0x02;
			}
			else if(ADMUX == 0 && tmpA >560){//left
				tmpC = 0x01;
			}
			else if(ADMUX == 0 && ( tmpA<=560 ) && ( tmpA>=50) ){
				tmpC = 0x00;
			}
			else{
				tmpC = 0x00;
			}
			if((((~PINB) & 0x01) == 0x01)){ //reset
				tmpC = 0x03;
			}

			
			if(ADMUX == 1){
				tmpC = 0x00;
			}

			if(USART_IsSendReady(0)) {
				USART_Send(tmpC, 0);
			}
			if(USART_HasReceived(0)){
				score = USART_Receive(0);
			}
			PORTB = tmpA;
			break;
		default:
			break;		
	}

}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	
	// Set the Timer and turn it on
	TimerSet(100);
	TimerOn();
	
	LCD_init();
	ADC_init();
	
	// Initialize USART
	initUSART(0);
	state = Start;
	while(1)
	{
		tick();

		
		while(!TimerFlag);
		TimerFlag = 0;
	}
}