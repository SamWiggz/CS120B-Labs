#include "rims.h"

/*	Partner(s) Name & E-mail: Samuel Wiggins (swigg002@ucr.edu) Leo Ortega (lorte007@ucr.edu)
 *	Lab Section: 021
 *	Assignment: Lab #1  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 
void main() {
   unsigned long result;
   unsigned char i;
   while (1) {
      result = 1; 
      i = 1;
      while (i <= A) {
         result = result * 2;
         puts(" Iteration: "); puti(i); puts("\n");
         i = i + 1;
      }
      puts("Result: "); puti(result); puts("\n\n");
      B = result;
   }
}
