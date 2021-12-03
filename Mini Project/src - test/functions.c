/* time4io.c

   This file written 2021-10-01 by Julia Wang

   For copyright and licensing, see file COPYING */

#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"

/* getbtns()
      
   Return: The three LSB contains data of the pushed buttons BTN 4 to 2.
*/
int getbtns() {
   volatile int* portD = (volatile int*) PORTD;
   int status = (*portD >> 5) & 0x7; // AND-mask to clear
   return status;
}

/*  
	To debug
*/
void tickLED(short light) {
  volatile int* led = (volatile int*) 0xbf886110; // PORTE
  *led = light;
}

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* General initializations goes here */
void init( void )
{
    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	// LED
	// The 8 LSB are set as 0 to indicate it is output
  	int* trisE = (int*) 0xbf886100; // Doesn't need to be volatile as it is the direction which only needs to be initialized once
  	trisE[1] = 0xff; // TRISECLR should be 4 bytes(1 int place) away from TRISE start, only the marked bits should be cleared to 0

	// Switches and Buttons
  	// Set bits 11 to 5 as 1 which sets the switches and buttons as input
	TRISD |= 0xfe0;
}
