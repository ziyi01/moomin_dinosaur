/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* Declare a helper function which is local to this file */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

#define ARRAY_SIZE 512

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/*  spi_send_recv
	Sends data to the display through the SPI Buffer.
	
	See Family Data Sheet SPI1-2 Registers and Serial Peripheral Interface.
*/
void spi_send_recv(uint8_t data) {
	// Checks for SPIRBF = 1, SPITBE = 0
	// SPIRBF = SPI Receive Buffer, SPITBE = Transmit Buffer Empty
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1)); // If buffer has not received, wait till done
}

/*	Display-functions  */

void display_pixel(int x, int y) {
	if(x < 128 && y < 32 && x >= 0 && y >= 0) {
		int block = y / 8;
		int yOff = y % 8;
		image[block*128+x] = image[block*128+x] | 0x1 << yOff;
	}
}

void clear_pixel(int x, int y) {
	if(x < 128 && y < 32 && x >= 0 && y >= 0) {
		int block = y / 8;
		int yOff = y % 8;
		image[block*128+x] = image[block*128+x] | 0x0 << yOff;
	}
}

void clear_display() {
	int i;
	for(i = 0; i < ARRAY_SIZE; i ++) {
		image[i] = 0x00;		
	}
}

/*  display_update
	Send the data array to the render buffer
*/
void display_update(void) {
	int i, j;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;	

		for(j = 0; j < ARRAY_SIZE/4; j ++) {
			spi_send_recv(image[j]);
		}
	}
}

/* Initialization */
void display_init(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}