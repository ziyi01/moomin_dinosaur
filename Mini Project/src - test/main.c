/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declatations for these labs */

/*
  Uses getbtns() and getsw() from time4io to retrieve the status of
  the Switches and Buttons 2-4 to update the time on display.

*/
void checkButton() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) return; // Return if nothing is registered
  
  if((btns & 0x1) == 1) {
    //FILL
  } 
  if((btns & 0x2) == 2) {
    //FILL
  }
  if((btns & 0x4) == 4) {
    //FILL
  }
}

/*
  The game loop
*/
void game() {
  checkButton();

  //FILLLL
  display_update();
}

int main(void) {
	init();

	display_init();
	display_update();

	int i, j;	
	for(i = 0; i < 4; i ++) {
		for(j = 0; j < 4; j ++) {
			display_pixel(i, j);
		}
	}

	while( 1 )
	{
    game();
	}
	return 0;
}
