/*
 * demo.c
 *
 * Created: 2/4/2019 4:41:10 PM
 * Author : samwi
 */ 

#include <avr/io.h>


int main(void)
{
    DDRB = 0x00; PORTB = 0xFF;
    while (1) 
    {
		PORTB = 0xFF;
    }
}

