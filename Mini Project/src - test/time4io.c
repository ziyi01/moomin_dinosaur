/* time4io.c

   This file written 2021-10-01 by Julia Wang

   For copyright and licensing, see file COPYING */

#include <stdint.h>   
#include <pic32mx.h>  
#include "mipslab.h"

/*
   Assignment 1 f)
   Function prototype: int getsw(void);
   Parameter: none

   Return: The four LSB contains the data from switches SW4 to 1;
*/
int getsw() {
   volatile int* portD = (volatile int*) PORTD;
   int status = (*portD >> 8) & 0xf; // AND-mask to clear the rest of the bits
   return status;
}

/*
   Assignment 1 g)
   Function prototype: int getbtns(void)
   Parameter: none
   
   Return: The three LSB contains data of the pushed buttons BTN 4 to 2.
*/
int getbtns() {
   volatile int* portD = (volatile int*) PORTD;
   int status = (*portD >> 5) & 0x7; // AND-mask to clear
   return status;
}